/************************************************************
 * Parser of the project                                    *
 * Copyright (C) 2021 Yupeng Hou  a1783922                  *
 *                                                          *
 * This file is globally used in this project. It provide   *
 * commonly used variables and functions                    *
 *                                                          *
 * @file publicUse.h                                        *
 * @brief this head contain all commonly used variables and *
 * functions                                                *
 *                                                          *
 * @author  Yupeng Hou                                      *
 * @email   a1783922@student.adelaide.edu.au                *
 * @version 1.3                                             *
 * @comments by He Zhang                                    *
 * @email   a1804981@student.adelaide.edu.au                *
 ************************************************************/

#ifndef PARSER_H
#define PARSER_H
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>

using namespace std;

/******************************************
 * @brief a name space for appandReader   *
 * It significantly shorten the type name *
 * of maps in the appandReader            *
 ******************************************/
namespace Appand_map {
typedef map<string, string> group;
typedef pair<group *, group *> publication;
typedef map<string, publication *> map;
} // namespace Appand_map

string rootPathStr = std::filesystem::current_path();

void initialRootPath() {
  // regex trimPath("((.*/)*app)");
  regex trimPath("((.*/)*Team-21)");
  smatch acquiredPath;
  if (regex_search(rootPathStr, acquiredPath, trimPath)) {
    rootPathStr = acquiredPath.str();
  } else {
    cout << rootPathStr << endl;
    __throw_runtime_error("Unrecognised path.");
  }
}

static std::chrono::time_point<std::chrono::system_clock> NOW =
    std::chrono::system_clock::now();

static ofstream writeLog; // log writer /** might needed
                          // at anywhere */
static void writeLogMessage(const char *message) {
  NOW = std::chrono::system_clock::now();
  const std::time_t t_c = std::chrono::system_clock::to_time_t(NOW);
  writeLog << std::put_time(std::localtime(&t_c), "%F %T. ") << message << endl;
}
static const string CAPITIAL = {
    "QWERTYUIOPASDFGHJKLZXCVBNM"}; // all capitial letters /** needed for locate
                                   // them in string */
static short outputLevel = 0;      // switch the output level

/******************************
 * @brief define tabes        *
 * different tab elements for *
 * outputing html files       *
 ******************************/
static const string tab1 = "  ";
static const string tab2 = "    ";
static const string tab3 = "      ";
static const short YEAR = 1;
static const short CONF = 2;
static const short NAME = 3;
static const short PUBL = 4;

/************************************
 * @brief sets to store information *
 * as a list of parsed information  *
 * it not need to keep the same     *
 * class nor numbers of them        *
 ************************************/
static set<int> Years;
static set<string> Types;
static set<string> Researchers;
static set<string> Conferences;
static map<string, int> ConferencesCount;

/*****************************************
 * @brief predefined avaliable aspects   *
 * lable all other aspects as not needed *
 *****************************************/
enum AvaliableAspects {
  enum_NotNeeded,
  enum_Title,
  enum_Year,
  enum_Author,
  enum_Editor,
  enum_Url,
  enum_Number,
  enum_Pages,
  enum_Journal,
  enum_Volume
};

/*******************************************
 * @brief predefined avaliable types       *
 * lable all other aspects as unrecognised *
 *******************************************/
enum typesList {
  enum_unRecognizsd,
  enum_books,
  enum_conf,
  enum_journals,
  enum_phd,
  enum_series,
  enum_reference,
};

/*****************************************
 *  @brief maps for map string to enums  *
 *****************************************/
static map<string, AvaliableAspects> mapFieldNames;
static map<string, typesList> mapTypes;

/***************************************************
 * @brief initialise all string-enum maps          *
 * @note needed be edited with corresponding enums *
 * @see enum AvaliableAspects                      *
 *      enum typesList                             *
 ***************************************************/
void InitializeEnum() {
  mapFieldNames["title"] = enum_Title;
  mapFieldNames["year"] = enum_Year;
  mapFieldNames["author"] = enum_Author;
  mapFieldNames["editor"] = enum_Editor;
  mapFieldNames["url"] = enum_Url;
  mapFieldNames["number"] = enum_Number;
  mapFieldNames["pages"] = enum_Pages;
  mapFieldNames["journal"] = enum_Journal;
  mapFieldNames["volume"] = enum_Volume;

  // all acceptable types
  mapTypes["books"] = enum_books;
  mapTypes["conf"] = enum_conf;
  mapTypes["journals"] = enum_journals;
  mapTypes["phd"] = enum_phd;
  mapTypes["series"] = enum_series;
  mapTypes["reference"] = enum_reference;
}

// globally used regex pattern
static regex entry("([[:alpha:]]+)[[:space:]]*=[[:space:]]\\{");
static regex dblpKey("DBLP:([[:alpha:]]*)/(.*)/(.*),");
static regex parseField("([[:alpha:]]+)[[:space:]]*= \\{(.*)\\},");
static regex
    parseNames("(([[:space:]]?([[:alpha:]]+([[:space:]][[:alpha:]]+)*?)[[:"
               "space:]]and)|([[:space:]]([[:alpha:]]+([[:space:]][[:alpha:]]+)"
               "*)$)|([[:alpha:]]*([[:space:]][[:alpha:]]+)*$))");

/**
 * @brief a general print vector function
 *
 * @param output the writing stream
 * @param outputVec the vector sample
 */
void printAVec(ofstream &output, vector<string> &outputVec) {
  for (auto i = outputVec.begin(); i != outputVec.end(); ++i) {
    if (i + 1 != outputVec.end()) {
      output << *i << ", ";
    } else {
      output << *i << endl;
    }
  }
}
void printAVec(ofstream &output, vector<int> &outputVec) {
  for (auto i = outputVec.begin(); i != outputVec.end(); ++i) {
    if (i + 1 != outputVec.end()) {
      output << *i << ", ";
    } else {
      output << *i << endl;
    }
  }
}

/********************************************************
 *  @brief Entry contain every needed field of a entry  *
 ********************************************************/
class Entry {
private:
  // Every entity must have
  string title;
  // Most entity must have
  short year;
  // For most of articles
  vector<string> Authors;
  // For those do not have authors
  vector<string> Editors;
  // A link for paper
  string url;
  // For conferences
  string confAbbr;
  // For articles
  string journal;
  string volume;
  // additional infor
  string number;
  string pages;
  // All local fields
  map<string, string> *localFields;

  bool hidden;

  // Basic functions
  // only needed inside the class
  inline string changeSymbolsInName(string &aName);
  inline void trimTitle(string &titleOle);
  inline void trimName(string &oldName);

public:
  // Few variables need publicly accessable
  vector<string> names;
  string type;
  string entryID;

  // Default constructor
  Entry() = default;
  // Constructor with name
  Entry(string name);
  void parseEntry(ifstream &input, ofstream &writeSingle);

  // Mutators
  inline void setConfAbbr(string &abbr);
  inline void writeLocalEntries(Appand_map::publication *input);

  // Accessors
  inline string acquireTags();
  inline vector<string> &acquireAuthors();
  inline string acquireThirdLine(int checking, string target);
  inline string &acquireTitle();
  inline short acquireYear();
  inline string &acquireUrl();
  inline string &acquireConf();
  inline string &acquireJournal();
  inline string &acquireType();
  inline Appand_map::group *acquireLocalEntries();
};

/****************************************************************
 *  @brief Entry contain every needed function for writing htmls*
 ****************************************************************/
class HTMLWriter {

  void checkSth(ofstream &output, vector<string> &input,
                string &name); /* write the checkbox */
  void yearCheck(ofstream &output, set<int> &years, bool checking);
  void typeCheck(ofstream &output, set<string> &types, bool links);
  void confCheck(ofstream &output, set<string> &confs, bool checking);
  void nameCheck(ofstream &output, set<string> &names, bool checking);
  void makeYear(vector<string> &output, set<int> &years);
  void makeType(vector<string> &output, set<string> &types);

  void writeCheckBoxes(ofstream &output, set<int> &years, set<string> &types,
                       set<string> &confs, set<string> &names, int setting,
                       bool link);
  void writeTheLine(ofstream &output, string &tag);
  void writeInfoLine(ofstream &writeHTMLE, string value, int num);
  void startWriting(ofstream &output, short head);
  void endWriting(ofstream &output);
  void writeNev(ofstream &output, vector<string> &list, bool link);
  void writeP(ofstream &output, Entry *object, bool needed, int checking,
              string target);
  void writePublications(ofstream &output, bool link);
  void writeHead(ofstream &output, set<int> &years, set<string> &types,
                 string &message, int setting);
  void autoWrite(ofstream &writeHTMLS, vector<Entry *> data, short head,
                 string &usingName);

public:
  void autoWriteAfile(short head);
  void writePublicationsHTML();
  void writeBasePublications();
};

static vector<Entry *> allWorks;

#endif
