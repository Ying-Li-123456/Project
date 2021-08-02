/**********************************************************************
 * Parser of the project                                              *
 * Copyright (C) 2021 Yupeng Hou  a1783922                            *
 *                                                                    *
 * This file is the entry of the whole program, it contain            *
 * the main function and some other associate functions               *
 *                                                                    *
 * @file parser.cpp                                                   *
 * @brief this file is the entry of the whole program                 *
 *                                                                    *
 * @author  Yupeng Hou                                                *
 * @email   a1783922@student.adelaide.edu.au                          *
 * @version 3.0                                                       *
 * @comments by He Zhang                                              *
 * @email   a1804981@student.adelaide.edu.au                          *
 **********************************************************************/

#include "appendReader.cpp"
#include "writeHTML.cpp"

static Appand_map::map readedAppend;

/*****************************************************
 * @brief remove duplicate entries based on dblp_key *
 *****************************************************/
void removeDuplicate() {

  // sort all works by dblp_key first, the entries
  // has the same dblp_key will be together
  sort(allWorks.begin(), allWorks.end(), SortByID);

  // all needed iterator
  auto previous = allWorks.begin();  /* iterator point at the previous one */
  auto start = allWorks.begin() + 1; /* iterator point at the second one */
  auto end = allWorks.end();         /* iterator point at the end of vector */

  // go through every work
  for (; start != end;) {
    // if the entry share the same dblp_key with the previous one
    if ((*previous)->entryID == (*start)->entryID) {
      // add the name into shared name vector of the entry
      (*previous)->names.push_back((*start)->names[0]);
      // update the iterators
      start = allWorks.erase(start);
      end = allWorks.end();
    } else {
      // new entry, update iterators
      previous = start;
      ++start;
    }
  }
}

/**
 * @brief the function for reading a BibTex
 *
 * @param readBib input stream, bind with th BibTex
 * @param researcher the researcher's name
 */
void readAnAuthor(ifstream &readBib, string &researcher) {

  ofstream writeSingle;
  string readedLine = "";         /* temporarily store readed line */
  Researchers.insert(researcher); /* record the researcher's name */

  // go through every lines
  while (getline(readBib, readedLine)) {

    // Store a entry
    Entry *currentEntry = new Entry(researcher);
    string noLash = "";

    // must start with a @
    if (readedLine[0] != '@') {
      cout << "BibTex format error encountered." << endl;
      cout << "An @ is expected." << endl << endl;
    }

    smatch parsedKey;
    if (regex_search(readedLine, parsedKey, dblpKey)) {
      noLash += (parsedKey[1].str() + parsedKey[2].str() + parsedKey[3].str());
      currentEntry->entryID = parsedKey[1].str() + '/' + parsedKey[2].str() +
                              '/' + parsedKey[3].str();
      currentEntry->type = parsedKey[1].str();
      // record the conference name if needed
      if (currentEntry->type == "conf") {
        string tempString = parsedKey[2].str();
        currentEntry->setConfAbbr(tempString);
      }
    }

    auto appending = readedAppend.find(currentEntry->entryID);
    if (appending != readedAppend.end() &&
        appending->second->second->find("HIDE") !=
            appending->second->second->end()) {
      delete currentEntry;
      currentEntry = nullptr;
      while (getline(readBib, readedLine) && readedLine != "") {
      }
      continue;
    }
    writeSingle.open("single_bib/" + noLash + ".bib");
    writeSingle << readedLine << endl;
    // use input to parse the content
    currentEntry->parseEntry(readBib, writeSingle);

    // check the local data
    if (appending != readedAppend.end()) {
      currentEntry->writeLocalEntries(appending->second);
    }

    // insert all info into sets
    Years.insert(currentEntry->acquireYear());

    if (currentEntry->type.empty()) {
      cout << "No type entry detected in dblp_key of: " << endl;
      cout << currentEntry->acquireTitle() << endl;
    }
    Types.insert(currentEntry->acquireType());

    if (currentEntry->acquireConf() != "None") {
      Conferences.insert(currentEntry->acquireConf());
    }

    allWorks.push_back(currentEntry);
  }
}

/***********************************************
 * @brief main function, read researcher list  *
 * initialise and execute the parsing progress *
 *                                             *
 * @return 0, represent correctly exit         *
 ***********************************************/
int main(void) {

  writeLogMessage("INFO Parser launched. ");
  initialRootPath();
  writeLog.open(rootPathStr + "/server/test/parser_log.txt");
  // read researcher list
  ifstream readList(rootPathStr + "/server/test/researcher_list.txt");
  // create directories to store all htmls
  std::filesystem::create_directory(rootPathStr + "/templates/single_person");
  std::filesystem::create_directory(rootPathStr + "/templates/years");
  std::filesystem::create_directory(rootPathStr + "/templates/conferences");
  std::filesystem::create_directory(rootPathStr + "/single_bib");
  cout << "The root path of the project: " << rootPathStr << endl;

  // bib reader
  ifstream readBib;
  // initialise the enumerate entries
  InitializeEnum();
  writeLogMessage("INFO Initiating local fields parsing sequence.");
  // read the append file, store the result globally
  readedAppend = readAppendEntries();

  writeLogMessage("INFO Start parsing, reading researcher_list.txt.");
  // Start parsing
  while (readList.good()) {

    // temporarily store the readed line
    string rawString;
    // store the researcher name
    string researcher = "";
    // read a line into rawString
    getline(readList, rawString);
    // store first word into reasearcher name
    researcher = rawString.substr(0, rawString.find(' '));

    // skip the empty line or incorrectly formated line
    if (!researcher.empty()) {
      // open a bib file
      cout << "Readed BibTex: " << researcher << endl;
      readBib.open(rootPathStr + "/bib_files/" + researcher + ".bib");

      writeLogMessage(("INFO Readed BibTex: " + researcher + ".bib").c_str());
      // call the function, read the file
      writeLogMessage("INFO Initiating parsing sequence.");
      readAnAuthor(readBib, researcher);
      writeLogMessage("INFO Parsing process completed.");

      // close the file
      readBib.close();
    }
  }

  // all BibTex readed, no result
  if (allWorks.empty()) {

    writeLogMessage("WARN No researcher founded.");

    // write a empty raw publications web page
    ofstream writeEmptyPublications(rootPathStr +
                                    "/templates/Publications.html");
    writeEmptyPublications
        << "{\% extends 'base.html' \%}" << endl
        << "{\% block main_content \%}" << endl
        << "<div class=\"content\"><h3>No reasearcher</h3><br><h4>You can "
           "login to the management system and add researchers.</h4></div>"
        << endl
        << "{\% endblock \%}" << endl;
  } else {
    // create a HTML writer
    HTMLWriter writeOne;

    writeLogMessage("INFO Initiating HTML files writing sequence.");
    writeOne.writeBasePublications();

    // Output researchers
    writeOne.autoWriteAfile(NAME);

    cout << "Total publications have readed: " << allWorks.size() << endl;
    removeDuplicate();
    writeLogMessage(("INFO Total publications have readed: " +
                     to_string(allWorks.size()) + "")
                        .c_str());

    // Output years
    writeOne.autoWriteAfile(YEAR);
    if (!Conferences.empty()) {
      // Output conferences
      writeOne.autoWriteAfile(CONF);
    }
    // Output publications
    writeOne.autoWriteAfile(PUBL);

    writeLog.close();
  }

  return 0;
}
