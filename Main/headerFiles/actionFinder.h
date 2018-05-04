//
// Created by a24run on 3/27/18.
//

#ifndef SQL_PARSER_1_5_ACTIONFINDER_H
#define SQL_PARSER_1_5_ACTIONFINDER_H

#include <vector>
bool is_number(const std::string& s);

void findDoaction(string query);

vector<string> split(const string &s, char delim);

vector< string> commasSeperationInternalQuery(string query);

string eraseSubStr(std::string & mainStr, const std::string & toErase);

string trim_copy(std::string s);

string erasequotes(string input);

#endif //SQL_PARSER_1_5_ACTIONFINDER_H
