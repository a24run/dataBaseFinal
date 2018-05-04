//
// Created by a24run on 3/28/18.
//

#ifndef SQL_PARSER_1_5_SELECT_H
#define SQL_PARSER_1_5_SELECT_H
void selectAction(string query,vector<string> tokens);

vector<vector<string>> oneSelector(vector<vector<string>> allData,string tableName,string selctor);

void pleasePrint(vector<vector<string>> allSolutions);

vector<string> subStringsWithoutDelimeter(string mainString, string delimiter);

vector<vector<string>> moreThanOneSelector(vector<vector<string>> allData,string tableName,string selector);
#endif //SQL_PARSER_1_5_SELECT_H
