//
// Created by a24run on 3/31/18.
//

#ifndef SQL_PARSER_1_5_BINARYREADWRITE_H
#define SQL_PARSER_1_5_BINARYREADWRITE_H

void writeToTBL(string tableName, vector<string> input);
vector<int> eachRowAndnumRecordsTbl(string tableName);
vector<vector<string>> readFromTBL(string tableName);
#endif //SQL_PARSER_1_5_BINARYREADWRITE_H
