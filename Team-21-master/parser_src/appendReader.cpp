/**********************************************************************
 * Parser of the project                                              *
 * Copyright (C) 2021 Yupeng Hou  a1783922                            *
 *                                                                    *
 * This file is designed to read the append information               *
 *                                                                    *
 *                                                                    *
 * @file appendReader.cpp                                             *
 * @brief this program read the bib_change.txt file extract all       *
 * information and reorganis that file                                *
 *                                                                    *
 * @author  Yupeng Hou                                                *
 * @email   a1783922@student.adelaide.edu.au                          *
 * @version 1.2                                                       *
 * @comments by He Zhang                                              *
 * @email   a1804981@student.adelaide.edu.au                          *
 **********************************************************************/

#include "Entry.h"

/****************************************
 * @brief all in one function           *
 *                                      *
 * @return return the Appand_map itself *
 ****************************************/
Appand_map::map readAppendEntries() {

  // open files
  ifstream readChange(rootPathStr + "/server/test/bib_change.txt");
  ofstream writeChange(rootPathStr + "/server/test/bib_change.txt.new");
  Appand_map::map readedEntries;

  string dblp_key;   /* record the dblp_key */
  string content;    /* a content */
  string readedLine; /* temporarily store the readed line */

  // read every line in the file
  // read the key first
  writeLogMessage("INFO Initiating change.txt parsing process.");
  while (getline(readChange, dblp_key)) {

    content = "";

    // create the node of the publication if is a new one
    if (readedEntries.find(dblp_key) == readedEntries.end()) {
      readedEntries[dblp_key] = new Appand_map::publication;
      // initialise the content
      readedEntries[dblp_key]->first = new Appand_map::group;
      readedEntries[dblp_key]->second = new Appand_map::group;
    }

    // read all content, till read a empty line
    while (getline(readChange, content) && content != "") {

      // parse a entry, acquire content and field name
      regex pattern("([[:alpha:]]*)=\\{(.*)\\},");
      smatch matchedWords;

      // fixed by He Zhang incase wrong input
      if (regex_search(content, matchedWords, pattern) &&
          !matchedWords[1].str().empty() && !matchedWords[0].str().empty()) {
        // output warning
        if (matchedWords[1].str() == "author" ||
            matchedWords[1].str() == "editor") {
          writeLogMessage("ERROR We do not support any modifications on "
                          "author list or "
                          "editor list for now.");
          continue;
        }
        if (matchedWords[1].str() == "HIDE") {
          writeLogMessage(("WARN Field " + matchedWords[1].str() +
                           " detected, entry " + dblp_key +
                           " will not show up.")
                              .c_str());
          writeLogMessage("INFO This parsing process will continue.");
        }

        // identity the entry
        // if it is a new field
        if (mapFieldNames[matchedWords[1].str()] == enum_NotNeeded) {

          // handle the delete
          if (matchedWords[2].str() == "DELETE") {

            // erase the node
            readedEntries[dblp_key]->second->erase(matchedWords[1].str());

            // output the status
            writeLogMessage(
                ("INFO Local field " + matchedWords[1].str() + " deleted.")
                    .c_str());

          } else {
            if (readedEntries[dblp_key]->second->find(matchedWords[1].str()) !=
                readedEntries[dblp_key]->second->end()) {

              // output the status
              writeLogMessage(
                  ("INFO New field " + matchedWords[1].str() + " detected.")
                      .c_str());
              writeLogMessage(
                  ("WARN Local field " + matchedWords[1].str() +
                   " already exist, it will be overwritten by the new "
                   "content.\n" +
                   "\tOld content: " +
                   (*(readedEntries[dblp_key]->second))[matchedWords[1].str()] +
                   "\n\tNew content: " + matchedWords[2].str())
                      .c_str());
            }
            // put it in or replace the old one
            (*(readedEntries[dblp_key]->second))[matchedWords[1].str()] =
                matchedWords[2].str();
            // output the status
            writeLogMessage(
                ("INFO Local field " + matchedWords[1].str() + " deployed.")
                    .c_str());
          }
          // if it is a duplicate field
        } else {
          // handle the delete
          if (matchedWords[2].str() == "DELETE") {
            readedEntries[dblp_key]->first->erase(matchedWords[1].str());
            writeLogMessage(
                ("INFO Duplicate field " + matchedWords[1].str() + " deleted.")
                    .c_str());
          } else {
            // output the status
            writeLogMessage(
                ("INFO Duplicate field " + matchedWords[1].str() + " detected.")
                    .c_str());
            writeLogMessage(("WARN Duplicate field " + matchedWords[1].str() +
                             " will overload the original field in BibTex "
                             "downloaded from DBLP.")
                                .c_str());
            // put it in or replace the old one
            (*(readedEntries[dblp_key]->first))[matchedWords[1].str()] =
                matchedWords[2].str();
          }
        }
      } else {
        writeLogMessage(
            ("ERROR Formating error detected.\n\t" + content).c_str());
      }
    }
  }

  writeLogMessage("INFO change.txt parsing process completed.");
  writeLogMessage("INFO Rewriting change.txt process initiating.");
  // rewrite the file
  for (auto aPublication : readedEntries) {

    // output the entry id
    if (!aPublication.second->first->empty() ||
        !aPublication.second->second->empty())
      writeChange << aPublication.first << endl;

    // output the duplicate content
    if (!aPublication.second->first->empty()) {
      for (auto aEntry : *(aPublication.second->first)) {
        writeChange << aEntry.first << "={" << aEntry.second << "}," << endl;
      }
    }

    // output the different content
    if (!aPublication.second->second->empty()) {
      for (auto aEntry : *(aPublication.second->second)) {
        writeChange << aEntry.first << "={" << aEntry.second << "}," << endl;
      }
    }

    // output a blank line
    writeChange << endl;
  }

  // close the file streams
  writeChange.close();
  readChange.close();
  // replace the old file
  remove((rootPathStr + "/server/test/bib_change.txt").c_str());
  rename((rootPathStr + "/server/test/bib_change.txt.new").c_str(),
         (rootPathStr + "/server/test/bib_change.txt").c_str());

  writeLogMessage("INFO Rewriting process completed.");
  writeLogMessage("INFO Local fields parsing process completed.");

  return readedEntries;
}
