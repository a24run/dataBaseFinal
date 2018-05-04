//
// Created by a24run on 4/21/18.
//

#ifndef SQL_PARSER_1_5_ORDERBY_H
#define SQL_PARSER_1_5_ORDERBY_H

vector<string> returnParamsOfQuery (string query,vector<string> tokens);

vector< vector<string>> orderByStarter(string query,vector<string> tokens);

void orderByInitial(string query,vector<string> tokens);
#endif //SQL_PARSER_1_5_ORDERBY_H
