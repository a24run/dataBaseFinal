//
// Created by a24run on 3/31/18.
//
#include <iostream>

using namespace std;

#include <stdlib.h>
#include <string>
#include <vector>

#include "../headerFiles/actionFinder.h"
#include "../catlog/tableClass.h"
#include "../headerFiles/catlog.h"
#include "../headerFiles/show.h"

void show(string query, vector<string> tockens){
    if(query.find("TABLES")!=string::npos){
        cout<<"TABLE NAME       "<<" COLUMNS        "<<endl;
        vector<TableClass> AllTables = returnAllTables();
        for (int i = 0; i < AllTables.size(); ++i) {
            cout<<AllTables[i].tablename<<"             "<<AllTables[i].columns;
            cout<<endl;
        }
    }
    else if(query.find("TABLE")){
        query=trim_copy(query);
        vector<string> tokens= split(query,' ');
        string tableName;
        TableClass table;
        for (int i = 0; i < tokens.size(); i++) {
            if(i==tokens.size()-1)
                tableName=split(tokens[i],';')[0];
        }
        if(checkTableExists(tableName)==1){
            table = returnTable(tableName);
            cout<<table.tablename<<"        "<<table.columns<<"PRIMARY KEY "<<trim_copy(table.primary_key)<<endl;
        }
        else{
            cout<<"Table does not exits"<<endl;
        }
    }
}