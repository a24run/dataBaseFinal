//
// Created by a24run on 3/27/18.
//
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include "../headerFiles/actionFinder.h" // using for split
#include "../headerFiles/create.h"
#include "../headerFiles/catlog.h"

void writeToCatlog(string tablename,string query){
    //cout<<"calling write to catlog"<<endl;
    writeCreate(tablename, query);
}

void createBinaryFile(string fileName){
    fstream file;
    file.open(fileName, ios::out);
    file.open(fileName, ios::binary |ios::in );
    if (file.is_open())
    {
        cout <<"Created successfully"<<endl;
        file.close();
    }
    else
        cout<<"Error in creating File";
}

void createAction(string query,vector<string> tokens){
    string tableName= tokens[2];
    if(tableName.find('(') != string::npos){
        tableName=split(tableName,'(')[0];
    }
    if(checkTableExists(tableName)!=1)
    {
        writeToCatlog(tableName,query);
        createBinaryFile(tableName.append(".tbl"));
    }
    else
        cout<<"Table exists"<<endl;
}

