//
// Created by a24run on 3/28/18.
//

#ifndef SQL_PARSER_1_5_CATLOG_H
#define SQL_PARSER_1_5_CATLOG_H
#include "../catlog/tableClass.h"
void createCatlog();
void writeCreate(string tableName, string query);
int checkTableExists(string tableName);
TableClass returnTable(string tableName);
vector<string> getDataTypesVectorFromCatlog(string tableName);
vector<int> getDatasizeOfTable(string tableName);
void writeInsertToCatlog(string tableName,vector <int> eachRowAndNumOfRecords);
vector<TableClass> returnAllTables();
vector<string> getSpecificLineOftable(string tableName,string specific);
#endif //SQL_PARSER_1_5_CATLOG_H
