//
// Created by a24run on 3/28/18.
//

#ifndef SQL_PARSER_1_5_TABLECLASS_H
#define SQL_PARSER_1_5_TABLECLASS_H

#include <iostream>
using namespace std;

class TableClass {
    public:
        string tablename;
        string columns;
        string primary_key;
        long recordsize;
        long totalSize;
        long records;
};
//TableClass::TableClass(string , string, long, long);


#endif //SQL_PARSER_1_5_TABLECLASS_H
