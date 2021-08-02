/**********************************************************************
 * Parser of the project                                              *
 * Copyright (C) 2021 Yupeng Hou  a1783922                            *
 *                                                                    *
 * This file provid Entry class which is the data structure           *
 * for every entry                                                    *
 *                                                                    *
 * @file Entry.h                                                      *
 * @brief this head contain all variables that a Entry needed,        *
 * and all functions that needed by constructing this data srtucture, *
 * and for other functions to access these data                       *
 * functions                                                          *
 *                                                                    *
 * @author  Yupeng Hou                                                *
 * @email   a1783922@student.adelaide.edu.au                          *
 * @version 2.0                                                       *
 * @comments by He Zhang                                              *
 * @email   a1804981@student.adelaide.edu.au                          *
 **********************************************************************/

#ifndef ENTRY
#define ENTRY
#include "publicUse.h"

/*******************************************************
 * @brief this function format the name of researchers *
 * add spaces befor every capabilitiesed latter        *
 * @param name  the reference of the original name     *
 *                                                     *
 * @return return the formated name, which is a new    *
 * string which is different with the original one     *
 * @pre return a same string if no changes             *
 *******************************************************/
string formatName(string &name) {

  string formatedName = "";

  // check every character
  for (auto ch : name) {

    // add space to the result
    // if encountered a capitial latter
    if (ch >= 65 && ch <= 90) {
      formatedName += ' ';
    }

    // add the letter to result anyway
    formatedName += ch;
  }

  // remove the space at the beginning
  if (formatedName[0] == ' ') {
    formatedName.erase(formatedName.cbegin());
  }

  return formatedName;
}

/****************************************************
 * @brief write the tip lines for duplicate warning *
 * @param field referenceof field name              *
 ****************************************************/
void writeLogWarning(string &field, string &newContent, string &oldContent) {
  writeLogMessage(("WARN Field " + field +
                   " already exist in the corresponding DBLP BibTex, it will "
                   "be overwritten by the local "
                   "content.\n" +
                   "\tDBLP content: " + oldContent +
                   "\n\tLocal content: " + newContent)
                      .c_str());
}

/************************************************************************
 *  @brief implementations, just return the local variables' reference  *
 ************************************************************************/
Entry::Entry(string name) {
  this->type = "Unknown";
  this->title = "";
  this->year = 0;
  this->confAbbr = "None";
  this->number = "";
  this->pages = "";
  this->journal = "";
  this->volume = "";
  this->url = "";
  this->localFields = nullptr;
  this->names.push_back(name);
  this->hidden = false;
}
string &Entry::acquireTitle() { return this->title; }
short Entry::acquireYear() { return this->year; }
string &Entry::acquireUrl() { return this->url; }
string &Entry::acquireConf() { return this->confAbbr; }
string &Entry::acquireJournal() { return this->journal; }
string &Entry::acquireType() { return this->type; }
map<string, string> *Entry::acquireLocalEntries() { return this->localFields; }

/*******************************************************************
 * @brief implementation, input the abbreviation of the conference *
 * @param abbr the input string, parsed from the dblp_key          *
 *                                                                 *
 * @pre capabilities all characters                                *
 *******************************************************************/
void Entry::setConfAbbr(string &abbr) {
  for (auto &ch : abbr) {
    ch = toupper(ch);
  }
  confAbbr = abbr;
}

/**************************************************
 * @brief read all parsed local fields, and input *
 * @param input pre-set type publication          *
 *                                                *
 * @pre read the map and parse all fields         *
 * overwrite the old field if duplicate           *
 * push into localFields if new                   *
 **************************************************/
void Entry::writeLocalEntries(Appand_map::publication *input) {

  string noLash = "";
  for (auto i : this->entryID) {
    if (i == '/') {
      continue;
    } else {
      noLash += i;
    }
  }
  ofstream writeSingle("single_bib/" + noLash + ".bib", ofstream::app);
  writeSingle << "Local fields{" << endl;

  // input duplicate fields if have
  if (!input->first->empty()) {
    writeLogMessage(
        ("WARN Duplicate field(s) detected in entry " + this->entryID + ".")
            .c_str());

    // iterate through the map
    for (auto i : *(input->first)) {

      string tempYear = to_string(this->year);
      string tempFieldName = i.first;
      writeSingle << "  " << setw(10) << setfill(' ') << left << i.first
                  << "= {" << i.second << "}," << endl;

      // output different tips based on field name
      switch (mapFieldNames[i.first]) {
      case enum_Title:
        writeLogWarning(tempFieldName, i.second, this->title);
        this->title = i.second;
        break;
      case enum_Year:
        writeLogWarning(tempFieldName, i.second, tempYear);
        this->year = stoi(i.second);
        break;
      case enum_Author:
        break;
      case enum_Editor:
        break;
      case enum_Url:
        writeLogWarning(tempFieldName, i.second, this->url);
        this->url = i.second;
        break;
      case enum_Number:
        writeLogWarning(tempFieldName, i.second, this->number);
        this->number = i.second;
        break;
      case enum_Pages:
        writeLogWarning(tempFieldName, i.second, this->pages);
        this->pages = i.second;
        break;
      case enum_Journal:
        writeLogWarning(tempFieldName, i.second, this->journal);
        this->journal = i.second;
        break;
      case enum_Volume:
        writeLogWarning(tempFieldName, i.second, this->volume);
        this->volume = i.second;
        break;
      default:
        break;
      }
    }
  }

  // input new local fields if have
  if (!input->second->empty()) {

    // use the copy of the pointer directly
    this->localFields = input->second;

    // write the log for all local fields
    writeLogMessage(
        ("INFO New field detected in entry " + this->entryID + ".").c_str());
    for (auto i : *(input->second)) {
      writeSingle << "  " << setw(10) << setfill(' ') << left << i.first
                  << "= {" << i.second << "}," << endl;
      writeLogMessage(
          ("INFO Writing local entry " + i.first + "\n\tContent: " + i.second)
              .c_str());
    }
  }
  writeSingle << "}" << endl;
  writeSingle.close();

  writeLogMessage("INFO Local field reading process complete.");
}

/******************************************************
 * @brief acquire tags for a entry                    *
 *                                                    *
 * @return return a combined string of all            *
 * needed tags for front-end, class of div            *
 * @pre all entries must have year type, if is not in *
 * a conference the confAbbr will be None, and        *
 * there at least one name, this should not return a  *
 * empty string                                       *
 ******************************************************/
string Entry::acquireTags() {
  string result = "";
  result +=
      to_string(this->year) + " " + this->type + " " + this->confAbbr + " ";
  for (auto aName : names) {
    result += (aName + " ");
  }
  return result;
}

/***********************************************
 * @brief return the reference of name vector  *
 * @return the authors if have, return editors *
 * if no author                                *
 ***********************************************/
vector<string> &Entry::acquireAuthors() {
  return Authors.empty() ? Editors : Authors;
}

/**********************************************************
 * @brief construct the third line for front-end          *
 * @param checking a number to verify the target identity *
 * @param target the target it self                       *
 *                                                        *
 * @return the constructed line                           *
 * @pre use checking to shift the output infor            *
 * use target to keep it from change into link            *
 * other parameters are links                             *
 **********************************************************/
string Entry::acquireThirdLine(int checking, string target) {

  string result = "";

  // only write third line for conference and journals
  if (type == "conf") {
    // write the conference abbreviation
    // if the target is this conf, no link
    result += (confAbbr == "None")
                  ? ""
                  : (((checking == 0 || target != confAbbr)
                          ? ("<a href=\"/Publications/conferences/" + confAbbr +
                             "\">" + confAbbr + "</a> ")
                          : (confAbbr + " ")));
    // write the year, if the target is this year, no link
    result += (((checking == 0 || (target != to_string(this->year))))
                   ? ("<a href=\"/Publications/years/" + to_string(this->year) +
                      "\">" + to_string(this->year) + "</a>" + ": ")
                   : (to_string(this->year) + ": "));
    result += (pages.empty()) ? "" : pages;
    // result += (" <a href=\"" + this->url + "\"
    // target=\"_blank\">[URL]</a>");
    result += "<br>";
  } else if (type == "journals") {
    string tempJour = journal;
    trimTitle(tempJour);
    // write the journal line, no link for them
    result += (journal.empty()) ? "" : (tempJour + " ");
    result += (number.empty()) ? "" : (number + ": ");
    result += (pages.empty()) ? "" : (pages + " ");
    result += (volume.empty()) ? "" : (volume + " ");
    result +=
        ("(" +
         (((checking == 0 || (target != to_string(this->year))))
              ? ("<a href=\"/Publications/years/" + to_string(this->year) +
                 "\">" + to_string(this->year) + "</a>")
              : (to_string(this->year))) +
         ")" + /* " <a href=\"" + this->url +
         "\" target=\"_blank\">[URL]</a> */
         "<br>");
  }

  return result;
}

/*****************************************************
 * @brief rewrite special denoted special characters *
 *                                                   *
 * @param aName the original name                    *
 *                                                   *
 * @return the new string of new name                *
 *****************************************************/
string Entry::changeSymbolsInName(string &aName) {

  regex bibSym("\\{\\\\([`'^\"])\\{\\\\?([[:alpha:]])\\}\\}");

  string newName = "";
  unsigned int prevPos = 0;

  // go through every match
  for (sregex_iterator it(aName.begin(), aName.end(), bibSym), end_it;
       it != end_it; ++it) {
    string newSym = "<span>&";
    newSym += it->str(2);

    switch (it->str(1)[0]) {
    case '`':
      newSym += "grave";
      break;
    case '\'':
      newSym += "acute";
      break;
    case '^':
      newSym += "circ";
      break;
    case '~':
      newSym += "tilde";
      break;
    case '"':
      newSym += "uml";
      break;
    default:
      break;
    }

    if (newSym != "&") {
      newSym += ";</span>";
      newName += aName.substr(prevPos, it->position() - prevPos);
      newName += newSym;
      prevPos = it->position() + 7;
    }
  }

  // if no newName return the old one
  if (newName.empty()) {
    return aName;
  } else {
    newName += aName.substr(prevPos);
    return newName;
  }
}

/*****************************
 * @brief replace {-} with - *
 *                           *
 * @param oldName            *
 *****************************/
void Entry::trimName(string &oldName) {
  auto start = oldName.find("{-}");
  if (start != string::npos) {
    oldName.replace(start, 3, "-");
  }
}

/******************************************
 * @brief remove all { and } and unicodes *
 *                                        *
 * @param oldTitle                        *
 ******************************************/
void Entry::trimTitle(string &oldTitle) {

  auto rmUnicode = oldTitle.find("unicode");

  while (rmUnicode != string::npos) {
    auto start = oldTitle.begin();
    auto end = oldTitle.begin();
    rmUnicode -= 2;
    start += rmUnicode;
    end += (rmUnicode + 16);
    oldTitle.replace(start, end, " ");
    rmUnicode = oldTitle.find("unicode");
  }

  auto it = oldTitle.begin();

  auto left = oldTitle.find("{");
  while (left != string::npos) {
    if (left != string::npos) {
      it += left;
      oldTitle.erase(it);
      it = oldTitle.begin();
      left = oldTitle.find("{");
    }
  }

  auto right = oldTitle.find("}");
  while (right != string::npos) {
    if (right != string::npos) {
      it += right;
      oldTitle.erase(it);
      it = oldTitle.begin();
      right = oldTitle.find("}");
    }
  }
}

/**************************
 * @brief parse all field *
 *                        *
 * @param input           *
 **************************/
void Entry::parseEntry(ifstream &input, ofstream &writeSingle) {

  string completeField = ""; /* store the complete field string */
  string readedLine = "";    /* temporary store readed line */

  // read every line until meet the blank line
  while (getline(input, readedLine) && !readedLine.empty()) {

    writeSingle << readedLine << endl;
    // read all lines for the field
    if (readedLine.find("},") == string::npos) {
      // skip the spaces
      auto start = readedLine.find_first_not_of(" ");
      readedLine = readedLine.substr(start, readedLine.size() - start);
      completeField += readedLine + " ";
      continue;
    }

    // skip the spaces
    auto start = readedLine.find_first_not_of(" ");
    readedLine = readedLine.substr(start, readedLine.size() - start);
    completeField += readedLine;

    smatch matchedContents;
    if (regex_search(completeField, matchedContents, parseField)) {

      string content =
          matchedContents[2].str(); /* store the content temporarily */
      // handle content differently
      switch (mapFieldNames[matchedContents[1].str()]) {
      case enum_Title:
        trimTitle(content);
        this->title = content;
        break;
      case enum_Year:
        this->year = stoi(matchedContents[2].str());
        break;
      case enum_Author:
        // extract names
        for (sregex_iterator aName(content.begin(), content.end(), parseNames),
             end_it;
             aName != end_it; ++aName) {
          if (!(*aName)[3].str().empty()) {
            Authors.push_back((*aName)[3].str());
          } else if (!(*aName)[1].str().empty()) {
            Authors.push_back((*aName)[0].str());
          }
        }
        break;
      case enum_Editor:
        for (sregex_iterator aName(content.begin(), content.end(), parseNames),
             end_it;
             aName != end_it; ++aName) {
          if (!(*aName)[3].str().empty()) {
            Authors.push_back((*aName)[3].str());
          } else if (!(*aName)[1].str().empty()) {
            Authors.push_back((*aName)[0].str());
          }
        }
        break;
      case enum_Url:
        for (auto i = content.begin(); i != content.end(); ++i) {
          if (*i == 92) {
            i = content.erase(i);
          }
        }
        this->url = content;
        break;
      case enum_Number:
        this->number = content;
        break;
      case enum_Pages:
        this->pages = content;
        break;
      case enum_Journal:
        this->journal = content;
        break;
      case enum_Volume:
        this->volume = content;
        break;
      default:
        break;
      }
    } else {
      writeLogMessage(("ERROR Unrecognised field format.\n\t" + completeField +
                       "\n\tExpected format: Field   = {CONTENT},")
                          .c_str());
    }
    // reset the completeField
    completeField = "";
  }
  writeSingle << endl;
  writeSingle.close();
}

#endif
