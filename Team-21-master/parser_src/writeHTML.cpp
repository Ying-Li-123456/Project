/**********************************************************************
 * Parser of the project                                              *
 * Copyright (C) 2021 Yupeng Hou  a1783922                            *
 *                                                                    *
 * This file define the HTML writer which write the html file         *
 *                                                                    *
 * @file writeHTML.cpp                                                *
 * @brief this file define all functions which needed for writing the *
 * corresponding html files in different format based on all entries  *
 *                                                                    *
 * @author  Yupeng Hou                                                *
 * @email   a1783922@student.adelaide.edu.au                          *
 * @version 2.0                                                       *
 * @comments by He Zhang                                              *
 * @email   a1804981@student.adelaide.edu.au                          *
 **********************************************************************/

#include "Entry.h"

/************************************************************
 * @brief all kinds of compare functions for sort algorithm *
 *                                                          *
 * @param firstOne the pointer of first entry               *
 * @param secondOne the pointer of second entry             *
 *                                                          *
 * @return the bool variable of the comparison              *
 ************************************************************/
bool SortByYear(Entry *firstOne, Entry *secondOne) {
  return firstOne->acquireYear() > secondOne->acquireYear();
}
bool SortByConf(Entry *firstOne, Entry *secondOne) {
  return firstOne->acquireConf() < secondOne->acquireConf();
}
bool SortByType(Entry *firstOne, Entry *secondOne) {
  return firstOne->acquireType() < secondOne->acquireType();
}
bool SortByID(Entry *firstOne, Entry *secondOne) {
  return firstOne->entryID < secondOne->entryID;
}
bool SortConf(string &firstOne, string &secondOne) {
  return ConferencesCount[firstOne] > ConferencesCount[secondOne];
}

/**********************************************************
 * @brief insert information into different sets for      *
 * future use in writing the checkboxes                   *
 *                                                        *
 * @param readingEntry the pointer of the readed entry    *
 * @param researchers the reference of the researcher set *
 * @param types the reference of the type set             *
 * @param conferences the reference of the conference set *
 * @param years the reference of the year set             *
 **********************************************************/
void insertIntoSets(Entry *readingEntry, set<string> &researchers,
                    set<string> &types, set<string> &conferences,
                    set<int> &years) {

  if (outputLevel == 3) {
    cout << "Insert into sets." << endl;
  }

  // Insert name
  for (auto aName : readingEntry->names) {
    researchers.insert(aName);
  }

  // Insert type
  if (readingEntry->type.empty()) {
    cout << readingEntry->acquireTitle() << endl;
    cout << "ERROR: Empty Type detected." << endl;
  }
  types.insert(readingEntry->acquireType());

  // Insert conf
  if (readingEntry->acquireConf() != "None") {
    conferences.insert((readingEntry)->acquireConf());

    if (ConferencesCount.find(readingEntry->acquireConf()) !=
        ConferencesCount.end()) {
      ++ConferencesCount[readingEntry->acquireConf()];
    } else {
      ConferencesCount.insert({readingEntry->acquireConf(), 1});
    }
  }

  // Insert year
  years.insert(readingEntry->acquireYear());

  if (outputLevel == 3) {
    cout << "Insert finished." << endl;
  }
}

/******************************************************
 * @brief format the tag, use the raw tag             *
 * find the matched formated name                     *
 *                                                    *
 * @param type the reference of the type namem string *
 *                                                    *
 * @return a copy of the formated name                *
 ******************************************************/
pair<string, short> formatTag(string &typeName) {
  short img_num;
  string newName;

  switch (mapTypes[typeName]) {
  case enum_books:
    img_num = 1;
    newName = "Books";
    break;
  case enum_conf:
    img_num = 2;
    newName = "Conferences";
    break;
  case enum_journals:
    img_num = 3;
    newName = "Journals";
    break;
  case enum_phd:
    img_num = 4;
    newName = "Phd thesis";
    break;
  case enum_series:
    img_num = 5;
    newName = "Series";
    break;
  case enum_reference:
    img_num = 6;
    newName = "Reference";
    break;
  default:
    cout << typeName << endl;
    cout << "Unrecognised type." << endl;
    break;
  }

  pair<string, short> result(typeName, img_num);

  return result;
}

void HTMLWriter::checkSth(ofstream &output, vector<string> &input,
                          string &name) {

  // initialise counter
  // count how many lables
  int counter = 0;

  // iterate through every entry
  for (auto thing : input) {
    output << tab3 << tab2 << "<label"
           << (name == "select_conference" && counter == 5 ? " id=\"Sixth\""
                                                           : "")
           << ">" << endl;
    output << tab3 << tab3 << "<input type=\"checkbox\" value=\"" << thing
           << "\" name=\"" << name << "\" checked=\"checked\"> "
           << ((name == "select_researcher") ? (formatName(thing)) : thing)
           << (name == "select_conference"
                   ? "(" + to_string(ConferencesCount[thing]) + ")"
                   : "")
           << endl;
    output << tab3 << tab2 << "</label>" << endl;
    ++counter;
  }

  if (name == "select_conference" && counter >= 6) {
    output << "<a id=\"folder\" onclick=\"folder()\">[Fold]</a>" << endl;
  }
}

void HTMLWriter::yearCheck(ofstream &output, set<int> &years, bool checking) {

  output << tab3 << "<div id=\"check-year-content\" "
         << (checking ? "" : "style=\"display:none\"") << ">" << endl;

  output << tab2 << tab2 << "<p>Years:" << endl;

  for (auto year : years) {
    output << tab3 << tab2 << "<label>" << endl;
    output << tab3 << tab3 << "<input type=\"checkbox\" value=\"" << year
           << "\" name=\"select_year\" checked=\"checked\"> " << year << endl;
    output << tab3 << tab2 << "</label>" << endl;
  }

  output << tab2 << tab3 << "<button id=\"select-year-all\">select all</button>"
         << endl;
  output << tab2 << tab3
         << "<button id=\"deselect-year-all\">deselect all</button>" << endl;

  output << tab2 << tab2 << "</p>" << endl;

  output << tab3 << "</div>" << endl;
}

void HTMLWriter::typeCheck(ofstream &output, set<string> &types, bool links) {
  output << tab3 << "<div id=\"check-type-content\">" << endl;

  output << tab2 << tab2 << "<p>Types:" << endl;

  short img_num = 0;
  string typeName;
  for (auto type : types) {

    typeName = type;
    img_num = formatTag(typeName).second;

    output << tab3 << tab2 << "<label>" << endl;
    output << tab3 << tab3 << "<input type=\"checkbox\" value=\"" << type
           << "\" name=\"select_type\" checked=\"checked\"> " << typeName
           << endl;
    output << tab3 << tab2 << "</label>" << endl;
    if (links) {
      output << tab3 << tab2
             << "<img src={{ url_for( 'static', filename=\"images/" << img_num
             << ".png\" ) }} width=\"12\" height=\"12\" />" << endl;
    } else {
      output << tab3 << tab2 << "<img src=\"images/" << img_num
             << ".png\" width=\"12\" height=\"12\" />" << endl;
    }
  }

  output << tab2 << tab3 << "<button id=\"select-type-all\">select all</button>"
         << endl;
  output << tab2 << tab3
         << "<button id=\"deselect-type-all\">deselect all</button>" << endl;

  output << tab2 << tab2 << "</p>" << endl;

  output << tab3 << "</div>" << endl;
}

void HTMLWriter::confCheck(ofstream &output, set<string> &confs,
                           bool checking) {

  output << tab3 << "<div id=\"check-conference-content\" "
         << (checking ? "" : "style=\"display:none\"") << ">" << endl;

  output << tab2 << tab2 << "<p>Conferences:" << endl;

  if (confs.empty()) {
    output << "None.";
  } else {
    vector<string> tempConferences;
    for (auto aConf : confs) {

      tempConferences.push_back(aConf);
    }
    sort(tempConferences.begin(), tempConferences.end(), SortConf);

    string name = "select_conference";
    checkSth(output, tempConferences, name);

    output << tab2 << tab3
           << "<button id=\"select-conference-all\">select all</button>"
           << endl;
    output << tab2 << tab3
           << "<button id=\"deselect-conference-all\">deselect all</button>"
           << endl;
  }

  output << tab2 << tab2 << "</p>" << endl;

  output << tab3 << "</div>" << endl;
}

void HTMLWriter::nameCheck(ofstream &output, set<string> &names,
                           bool checking) {

  output << tab3 << "<div id=\"check-researcher-content\" "
         << (checking ? "" : "style=\"display:none\"") << ">" << endl;

  output << tab2 << tab2 << "<p>Researchers:" << endl;

  string name = "select_researcher";
  vector<string> tempNames;

  for (auto aName : names) {
    if (aName.empty()) {
      cout << "233: Empty Name." << endl;
    }
    tempNames.push_back(aName);
  }

  checkSth(output, tempNames, name);

  output << tab2 << tab3
         << "<button id=\"select-researcher-all\">select all</button>" << endl;
  output << tab2 << tab3
         << "<button id=\"deselect-researcher-all\">deselect all</button>"
         << endl;

  output << tab2 << tab2 << "</p>" << endl;

  output << tab3 << "</div>" << endl;
}

void HTMLWriter::makeYear(vector<string> &output, set<int> &years) {
  int result = 0;

  // special tag for newest year
  result = *years.rbegin() % 100 / 10;
  output.push_back(to_string(result) + "0");

  // all the normal years
  // MARK2
  for (auto aYear = ++years.rbegin(); aYear != years.rend(); ++aYear) {
    if (!((*aYear % 100 - 9) % 10)) {
      result = (*aYear % 100) / 10;
      output.push_back(to_string(result) + "0");
    }
  }
}

void HTMLWriter::makeType(vector<string> &output, set<string> &types) {
  for (auto type : types) {
    output.push_back(type);
  }
}

void HTMLWriter::startWriting(ofstream &output, short head) {

  if (head - 4) {
    output << "{\% extends 'base_publications.html' %}\r\n\r\n{\% block "
              "main_content %}"
           << endl
           << endl;

  } else {
    output << "{\% extends 'base.html' \%}" << endl
           << "{\% block main_content \%}" << endl
           << tab1 << "<div class=\"content\">" << endl
           << tab2 << "<h2>Publications</h2>" << endl
           << tab2 << "<p>There are " << allWorks.size()
           << " different publications in this group. </p>" << tab2
           << "<p>All publications entries are listed as following: </p>"
           << endl
           << endl;
  }
}

void HTMLWriter::endWriting(ofstream &output) {
  output << tab3 << "</div>" << endl;
  output << tab3 << "<a id=\"bottom\" href=\"#top\"></a>" << endl;

  output << "{\% endblock \%}" << endl;
  output.close();
}

void HTMLWriter::writeCheckBoxes(ofstream &output, set<int> &years,
                                 set<string> &types, set<string> &confs,
                                 set<string> &names, int setting, bool link) {

  output << tab2 << "<div class=\"checkbox_content\">" << endl;
  yearCheck(output, years, setting - 1);
  typeCheck(output, types, link);
  confCheck(output, confs, setting - 2);
  nameCheck(output, names, setting - 3);
  output << tab2 << "</div>" << endl;
  if (link) {
    output << tab2
           << "<script src={{ url_for('static', filename=\"js/button.js\") "
              "}}></script>"
           << endl
           << endl;
  } else {
    output << tab2 << "<script src=\"js/button.js\"></script>" << endl << endl;
  }
}

void HTMLWriter::writeTheLine(ofstream &output, string &tag) {
  output << tab3 << tab2 << "<h4 id=\"" + tag + "\" ></h4>" << endl << endl;
}

void HTMLWriter::writeNev(ofstream &output, vector<string> &list, bool link) {

  output << tab3 << "<div class=\"empty\">" << endl
         << tab3 << tab1 << "<div class=\"quick_link\">" << endl
         << tab3 << tab2 << "<a href=\"#top\" title=\"jump to top\">" << endl
         << tab3 << tab3
         << (link ? "<img src={{ url_for( 'static', "
                    "filename=\"images/top.dark.png\" ) }} alt=\"top\">"
                  : "<img src=\"images/top.dark.png\" alt=\"top\">")
         << endl
         << tab3 << tab2 << "</a><br/>" << endl;

  for (auto aPos = list.begin(); aPos != list.end(); ++aPos) {

    string tempTag = *aPos;

    switch (mapTypes[*aPos]) {
    case enum_books:
      // tempTag = "Books";
      tempTag = "B";
      break;
    case enum_conf:
      // tempTag = "Conferences";
      tempTag = "C";
      break;
    case enum_journals:
      // tempTag = "Journals";
      tempTag = "J";
      break;
    case enum_phd:
      // tempTag = "Phd thesis";
      tempTag = "P";
      break;
    case enum_series:
      // tempTag = "Series";
      tempTag = "S";
      break;
    case enum_reference:
      // tempTag = "Series";
      tempTag = "R";
      break;
    default:
      tempTag = "'" + *aPos + "s";
      break;
    }

    output << tab3 << tab2 << "<a href=\"#" << *aPos << "\">" << endl
           << tab3 << tab3 << "<span class=\"side-year\">" << endl
           << tab3 << tab3 << tab1 << "<small>" << tempTag << "</small>" << endl
           << tab3 << tab3 << "</span>" << endl
           << tab3 << tab2 << "</a><br/>" << endl;
  }

  output << tab3 << tab2 << "<a href=\"#bottom\" title=\"jump to bottom\">"
         << endl
         << tab3 << tab3
         << (link ? "<img src={{ url_for( 'static', "
                    "filename=\"images/bottom.dark.png\" ) }} alt=\"bottom\">"
                  : "<img src=\"images/bottom.dark.png\" alt=\"bottom\">")
         << endl
         << tab3 << tab2 << "</a><br/>" << endl
         << tab3 << "</div>" << endl
         << tab2 << "</div>" << endl
         << endl;
}

void HTMLWriter::writeP(ofstream &output, Entry *object, bool needed,
                        int checking, string target) {
  string temp;
  temp = object->acquireTags();
  output << tab2 << tab3 << "<div class=\"" << temp << "\">" << endl;
  // output << tab2 << tab3 << "<p>" << endl;
  // output << tab2 << tab3 << "<p class=\"" << temp << "\">" << endl;
  vector<string> tempVec;
  tempVec = object->acquireAuthors();
  for (auto aAuthor : tempVec) {
    temp = aAuthor;
    for (auto i = temp.begin(); i < temp.end(); ++i) {
      if (*i == ' ') {
        temp.erase(i);
      }
    }
    output << tab3 << tab3
           << ((Researchers.count(temp) &&
                (!(needed && temp == object->names[0])))
                   ? ("<a href=\"/Publications/single_person/" + temp + "\">" +
                      aAuthor + "; </a>")
                   : (aAuthor + "; "))
           << endl;
  }
  output << tab3 << tab3 << "<br>" << endl;

  temp = object->acquireTitle();
  output << tab3 << tab3 << temp << "<br>" << endl;
  // output << tab3 << tab3 << "<a href=\"" << object->acquireUrl()
  //        << "\" target=\"_blank\">" << temp << "</a><br>" << endl;

  temp = object->acquireThirdLine(checking, target);
  if (!temp.empty()) {
    output << tab3 << tab3 << temp << endl;
    output << tab3 << tab3 << "[Available: "
           << "<a href=\"" << object->acquireUrl()
           << "\" target=\"_blank\"> URL</a>]<br>" << endl;
  }

  if (object->acquireLocalEntries() != nullptr) {
    output << tab3 << tab3 << "Local entries: <br>" << endl;
    auto tempPtr = object->acquireLocalEntries();
    for (auto i : *tempPtr) {
      output << tab3 << tab3 << tab1 << i.first << ":\t" << i.second << "<br>"
             << endl;
    }
  }

  output << tab3 << tab3 << "{\% if login_status == '1' \%}" << endl
         << tab3 << tab3 << "<form action=\"/admin/edit\" >" << endl
         << tab3 << tab3 << "<input type=\"hidden\"" << endl
         << tab3 << tab3 << "name=\"url\"" << endl
         << tab3 << tab3 << "value=\"" << object->entryID << "\">" << endl
         << tab3 << tab3
         << "<button  type=\"submit\" value ='submit'>Edit</button>" << endl
         << tab3 << tab3 << "</form>" << endl
         << tab3 << tab3 << "{\% endif \%}" << endl;

  // output << tab2 << tab3 << "</p>" << endl << endl;
  output << tab2 << tab3 << "</div>" << endl << endl;
}

void HTMLWriter::writePublications(ofstream &output, bool link) {
  output << tab2 << "<ul>" << endl
         << tab3 << "<li id=\"year\">" << endl
         << tab3 << tab1 << "years:" << endl;
  for (auto aYear : Years) {
    output << tab3 << tab1 << "<a href=\""
           << (link ? "/Publications/years/" : "") << aYear
           << (link ? "" : ".html") << "\">" << aYear << ", </a>" << endl;
  }
  output << tab3 << "</li>" << endl
         << tab3 << "<li id=\"researcher\">" << endl
         << tab3 << tab1 << "researchers:" << endl;
  for (auto aResearcher : Researchers) {
    output << tab3 << tab1 << "<a href=\""
           << (link ? "/Publications/single_person/" : "") << aResearcher
           << (link ? "" : ".html") << "\">" << (formatName(aResearcher))
           << ", </a>" << endl;
  }
  output << tab3 << "</li>" << endl
         << tab3 << "<li id=\"conference\">" << endl
         << tab3 << tab1 << "conferences:" << endl;
  for (auto aConference : Conferences) {
    output << tab3 << tab1 << "<a href=\""
           << (link ? "/Publications/conferences/" : "") << aConference
           << (link ? "" : ".html") << "\">" << aConference << ", </a>" << endl;
  }
  output << tab3 << "</li>" << endl << tab2 << "</ul>" << endl;
}

void HTMLWriter::writeInfoLine(ofstream &writeHTMLE, string value, int num) {
  // writeHTMLE << "<div class=\"" << ((checking - 1) ? "year_head" :
  // "type_head")
  writeHTMLE << "<h1 class=\""
             << "info_head "
             << "\" id = \"" << value << "\" style=\"display: none;\">" << num
             << "</h1>" << endl;
}

void HTMLWriter::autoWrite(ofstream &writeHTMLS, vector<Entry *> data,
                           short head, string &fileName) {

  // initialise these four common set
  set<int> years;
  set<string> types;
  set<string> conferences;
  set<string> researchers;
  int count = 0;

  auto readingEntry = data.begin();
  string authorName = fileName;
  string currentHead = to_string((*readingEntry)->acquireYear());

  string tempTag =
      (to_string(((*readingEntry)->acquireYear() % 100) / 10) + "0");
  string firstTag = tempTag;

  // open these temp file
  // MARK3
  ofstream writeHTMLE(rootPathStr + "/templates/html.tmp");

  // update using name if needed
  if (head == YEAR) {
    // change tempTag for year
    tempTag = (*readingEntry)->acquireType();
    // change firstTag for year
    firstTag = tempTag;
    currentHead = (*readingEntry)->acquireType();
  } else if (head == NAME) {
    // add space for name
    authorName = formatName(fileName);
  }

  // write the first head first
  writeHTMLE << tab2 << tab2 << "<h3 id=\""
             << ((head - 1) ? to_string(data[0]->acquireYear()) : firstTag)
             << "\">"
             << ((head - 1) ? to_string(data[0]->acquireYear())
                            : (formatTag(firstTag)).first)
             << "</h3>" << endl;

  // read the list
  for (; readingEntry != data.end(); ++readingEntry) {

    // write output
    if (!conferences.empty() && conferences.begin()->empty()) {
      cout << "impossible" << endl;
    }
    insertIntoSets(*readingEntry, researchers, types, conferences, years);

    // if year file, head is type
    if (head == YEAR && (*readingEntry)->acquireType() != currentHead) {

      // temp outputHead string
      string outputHead;

      // update currentHead
      writeInfoLine(writeHTMLE, currentHead, count);
      count = 0;
      currentHead = (*readingEntry)->acquireType();

      // different types
      outputHead = formatTag(currentHead).first;

      // write the line if a new kind is appearing
      writeTheLine(writeHTMLE, currentHead);

      // write the head if a new kind is appearing
      writeHTMLE << tab2 << tab2 << "<h3 id=\"" << currentHead << "\">"
                 << outputHead << "</h3>" << endl;

      // for others, chronologically
    } else if ((head == CONF || head == NAME || head == PUBL) &&
               (*readingEntry)->acquireYear() != stoi(currentHead)) {

      // update currentHead
      writeInfoLine(writeHTMLE, currentHead, count);
      count = 0;
      currentHead = to_string((*readingEntry)->acquireYear());

      // write the line if need, except for first one
      // MARK2
      if ((*readingEntry)->acquireYear() != data[0]->acquireYear() &&
          !((((*readingEntry)->acquireYear()) % 100 - 9) % 10)) {
        tempTag =
            (to_string(((*readingEntry)->acquireYear() % 100) / 10) + "0");
        writeTheLine(writeHTMLE, tempTag);
      }

      // write the head
      writeHTMLE << tab2 << tab2 << "<h3 id=\"" << currentHead << "\">"
                 << currentHead << "</h3>" << endl;
    }

    // write the paragraph
    writeP(writeHTMLE, (*readingEntry), (head == NAME ? true : false), head,
           authorName);
    ++count;
  }
  // write last InfoLine
  writeInfoLine(writeHTMLE, currentHead, count);

  // close the temp files
  writeHTMLE.close();

  // write the start part
  startWriting(writeHTMLS, head);
  if (head == PUBL) {
    writePublications(writeHTMLS, true);
    writeHTMLS << tab3 << "</div>" << endl
               << tab3 << "<div class=\"line\"></div>" << endl;
  }

  vector<string> nevList;

  switch ((head == YEAR ? 2 : 1)) {
  case 1:
    makeYear(nevList, years);
    break;
  case 2:
    makeType(nevList, types);
    break;
  default:
    break;
  }

  writeNev(writeHTMLS, nevList, true);

  writeHTMLE << tab2 << "<div class=\"line\"></div>" << endl << endl;
  writeCheckBoxes(writeHTMLS, years, types, conferences, researchers, head,
                  true);

  // Write the first jump position manually
  writeHTMLS << tab2 << " <div class=\"publications\" id=\""
             << (head == YEAR ? "type" : "year") << "\">" << endl;
  // MARK1
  writeHTMLS << tab2 << "<div></div>" << endl;
  writeHTMLS << tab2 << "<p id=\"" << firstTag << "\"></p>" << endl;

  // read temp htmls
  // MARK3
  ifstream readHTMLE(rootPathStr + "/templates/html.tmp");
  string tmp;

  while (getline(readHTMLE, tmp)) {
    writeHTMLS << tmp << endl;
  }

  endWriting(writeHTMLS);

  remove((rootPathStr + "/templates/html.tmp").c_str());
}

void HTMLWriter::autoWriteAfile(short head) {
  string fileName; /* first head */
  string pathStr = rootPathStr + "/templates/";
  int i = 0;

  // initialise first element and path
  if (head == YEAR) {

    sort(allWorks.begin(), allWorks.end(), SortByYear);
    // start with first year
    fileName = to_string(allWorks[0]->acquireYear());
    pathStr += "years/";

  } else if (head == CONF) {

    sort(allWorks.begin(), allWorks.end(), SortByConf);
    // start with first not empty one
    for (; i < allWorks.size(); ++i) {
      fileName = allWorks[i]->acquireConf();
      if (fileName != "None") {
        break;
      }
    }

    pathStr += "conferences/";

  } else if (head == NAME) {

    // start with first name
    fileName = allWorks[0]->names[0];
    pathStr += "single_person/";
  } else if (head == PUBL) {
    sort(allWorks.begin(), allWorks.end(), SortByYear);
    // start with first year
    fileName = "Publications";
  }

  writeLogMessage(("INFO Start writing " + fileName + ".html").c_str());

  // initialise the writers
  ofstream writeOtherHTML;
  vector<Entry *> usingEntries = {};

  if (head - 4) {
    // using all publications
    for (; i < allWorks.size() + 1; ++i) {

      // If got the object with same parameter
      if ((i != allWorks.size()) &&
          ((head == YEAR &&
            to_string(allWorks[i]->acquireYear()) == fileName) ||
           (head == CONF && allWorks[i]->acquireConf() == fileName) ||
           (head == NAME && allWorks[i]->names[0] == fileName))) {

        usingEntries.push_back(allWorks[i]);

        // If got different
      } else {
        // sort what we have acquired
        if (head == YEAR) {
          sort(usingEntries.begin(), usingEntries.end(), SortByType);
          // cout << "679.New year: " << fileName << endl;
        } else {
          sort(usingEntries.begin(), usingEntries.end(), SortByYear);
          // cout << "684.New researcher: " << fileName << endl;
        }

        // Open the output file
        // MARK3
        writeOtherHTML.open(pathStr + fileName + ".html");

        // write the publication list
        ConferencesCount.clear();
        autoWrite(writeOtherHTML, usingEntries, head, fileName);
        ConferencesCount.clear();

        // clear the repo
        usingEntries.clear();

        if (i != allWorks.size()) {
          // update the head
          if (head == YEAR) {
            fileName = to_string(allWorks[i]->acquireYear());
          } else if (head == CONF) {
            for (; i < allWorks.size(); ++i) {

              fileName = allWorks[i]->acquireConf();
              if (fileName != "None") {
                break;
              }
            }
          } else if (head == NAME) {
            fileName = allWorks[i]->names[0];
          }

          if (fileName == "None") {
            cout << "Logic ERROR at line " << __LINE__ << endl;
            break;
          }
          // put in the new one
          usingEntries.push_back(allWorks[i]);
        }
      }
    }

  } else {
    // MARK3
    writeOtherHTML.open(pathStr + fileName + ".html");

    // write the publication list
    ConferencesCount.clear();
    autoWrite(writeOtherHTML, allWorks, head, fileName);
    ConferencesCount.clear();
  }
  writeLogMessage(("INFO Finish writing " + fileName + ".html").c_str());
}

void HTMLWriter::writeBasePublications() {
  ifstream readOld(rootPathStr + "/templates/base_publications.html");
  ofstream writeNew(rootPathStr + "/templates/base_publications.html.new");

  string readedLine = "";

  while (getline(readOld, readedLine) &&
         readedLine != "<!-- From here, shell writen by Bruce -->") {
    writeNew << readedLine << endl;
  }

  writeNew << "<!-- From here, shell writen by Bruce -->" << endl;
  readOld.close();
  writePublications(writeNew, 1);
  writeNew << tab2 << "</div>" << endl
           << tab2 << "<div class=\"line\"></div>" << endl
           << endl
           << tab2 << "{\% block main_content \%}" << endl
           << tab2 << "{\% endblock \%}" << endl
           << tab2 << "<footer class=\"footer\">" << endl
           << tab3
           << "<div class=\"footerContent\">Copyright © 2021 MCI Team21</div>"
           << endl
           << tab2 << "</footer>" << endl
           << tab1 << "</div>" << endl
           << "</body>" << endl
           << "</html>" << endl;

  remove((rootPathStr + "/templates/base_publications.html").c_str());
  rename((rootPathStr + "/templates/base_publications.html.new").c_str(),
         (rootPathStr + "/templates/base_publications.html").c_str());
}
