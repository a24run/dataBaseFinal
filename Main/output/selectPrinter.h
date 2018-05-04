//
// Created by a24run on 4/6/18.
//

#ifndef SQL_PARSER_1_5_SELECTPRINTER_H
#define SQL_PARSER_1_5_SELECTPRINTER_H
#include <iostream>
#include <vector>
using namespace std;

class selectPrinter {
    public:
    vector<vector<string>> printer(vector<vector<string>> allData);                               // All data
    vector<vector<string>> printer(vector<vector<string>>allData , int specificColumn);           //Specific Column
    vector<vector<string>> printer(vector<vector<string>>allData , vector<int>columnsToPrint);    //Multiple Columns
    vector<vector<string>> printer(vector<int>allRowMAtches, vector<vector<string>>allData);      // Multiple Rows
    vector<vector<string>>printer(vector<vector<string>> moreThanOneSelector, vector< vector<string>> whereSelectorResult);  //columns, Where

};


#endif //SQL_PARSER_1_5_SELECTPRINTER_H
