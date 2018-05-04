//
// Created by a24run on 3/28/18.
//
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "tableClass.h"
#include "../headerFiles/actionFinder.h"// for split
#include "../headerFiles/charTextManage.h"

using namespace std;

vector<string> getDataTypesVectorFromQ(string columns){
    vector<string> tableColumnValues =split(columns,',');
    vector<string> dataTypes;
    string lengthString;
    for (int i = 0; i < tableColumnValues.size(); i++) {
        if(tableColumnValues[i].find("INT")!=string::npos){
            dataTypes.push_back("INT");
        }
        if(tableColumnValues[i].find("CHAR")!=string::npos){
           // cout<<"tableColumnValues is "<<tableColumnValues[i]<<endl;
            vector<string> temp = split(tableColumnValues[i],' ');
            for (int j = 0; j < temp.size();j++) {
                if(temp[j].find("CHAR")!=string::npos)
                {
                    lengthString = eraseSubStr(split(temp[j],'(')[1],")");
                    string temp=string("CHAR")+",";
                    string toBepushed=temp+lengthString;
                    //cout<<"to be pushed is "<<toBepushed<<endl;
                    dataTypes.push_back(toBepushed);
                }
            }
        }
    }
    return dataTypes;
}

vector<string> getSpecificLineOftable(string tableName,string specific){
    string line;
    ifstream file("catlog.txt");
    string specificLine;
    if(file.is_open())
    {
        while(getline(file,line)){
            if(line.find(tableName) != std::string::npos)
            {
                getline(file,line);
                if (line.find(specific) != std::string::npos) {
                    specificLine=line;
                    file.close();
                }
            }

        }
        file.close();
        //cout<<"specfic line is "<<specificLine<<endl;
    }
    else{
        cout<<"there is error in opening catlog "<<endl;
    }
    return vector<string>(split(specificLine,':'));
}

vector<string> getDataTypesVectorFromCatlog(string tableName){
    vector<string>columns = getSpecificLineOftable(tableName,"columns");
    return getDataTypesVectorFromQ(columns[1]);
}

vector<int> getDatasizeOfTable(string tableName){
    vector<string> CatlogdataTypes=getDataTypesVectorFromCatlog(tableName);
    vector< int > sizes;
    for (int i = 0; i < CatlogdataTypes.size(); i++) {
        if(CatlogdataTypes[i].find("INT")!=string::npos)
            sizes.push_back(4);
        else if (CatlogdataTypes[i].find("CHAR")!=string::npos)
        {   vector<string> value =split(CatlogdataTypes[i],',');
            int val = std::stoi(trim_copy(value[1]));
            //cout<<"length is"<<val<<endl;
            sizes.push_back(val);
        }
    }
    return sizes;
}

vector<TableClass> returnAllTables(){
    vector<TableClass> sendingEntireThing;
    TableClass presentTable;
    fstream file;
    file.open("catlog.txt", ios::in);
    string line;
    if(file.is_open()){
        while(getline(file,line)){
            if(line.find("tableName:") != std::string::npos)
            {
                presentTable.tablename=split(line,':')[1];
                getline(file,line);
                presentTable.columns=split(line,':')[1];
                getline(file,line);
                std::string str = "string";
                char *cstr = new char[str.length() + 1];
                strcpy(cstr, str.c_str());
                presentTable.records=atol(cstr);
                getline(file,line);
                char *cstt = new char[str.length() + 1];
                strcpy(cstt, str.c_str());
                sendingEntireThing.push_back(presentTable);
            }
        }
        file.close();
        return sendingEntireThing;
    }
    else
        cout<<"cant open catlog.txt";
}

TableClass returnTable(string tableName){
    TableClass presentTable;
    fstream file;
    file.open("catlog.txt", ios::in);
    string line;
    if(file.is_open()){
        while(getline(file,line)){
            if(line.find("tableName:"+tableName) != std::string::npos)
            {
                presentTable.tablename=split(line,':')[1];
                getline(file,line);
                presentTable.columns=split(line,':')[1];
                getline(file,line);
                presentTable.primary_key=split(line,':')[1];
                getline(file,line);
                //cout<<"plz"<< split(line,':')[1]<<endl;
                char *pEnd;
                presentTable.recordsize=strtoul(split(line,':')[1].c_str(),&pEnd,10);
                getline(file,line);
                presentTable.totalSize=strtoul(split(line,':')[1].c_str(),&pEnd,10);
                getline(file,line);
                presentTable.records=strtoul(split(line,':')[1].c_str(),&pEnd,10);
//                std::string str = line;
//                char *cstr = new char[str.length() + 1];
//                strcpy(cstr, str.c_str());
//                presentTable.records=atol(cstr);
//                getline(file,line);
//                char *cstt = new char[str.length() + 1];
//                strcpy(cstt, str.c_str());
                return presentTable;
            }
        }
    }
    else
        cout<<"cant open catlog.txt";
}
void createCatlog(){
    ofstream catlog ("catlog.txt", ios::app);
    if (catlog.is_open())
    {
        //cout<<"file open success"<<endl;
        catlog.close();
    }
    else cout << "Unable to Create file";
}

int checkTableExists(string tableName){

    string line;
    ifstream file("catlog.txt");
    if(file.is_open())
    {
        while(getline(file,line)){
            if (line.find("tableName:"+tableName) != std::string::npos) {
                //cout<<"table "<<tableName<<" Exists"<<endl;
                file.close();
                return 1;
            }
        }
        file.close();
        return 0;
    }
    else{
        cout<<"there is error in opening catlog "<<endl;
    }
}

void writeObjToCatlog(TableClass newTable){
    fstream file;
    file.open("catlog.txt", ios::app);
    if(file.is_open()){
        file<<"tableName:"<<newTable.tablename<<"\n";
        file<<"columns:"<<newTable.columns<<"\n";
        file<<"primary key:"<<newTable.primary_key<<"\n";
        file<<"recordsize:"<<newTable.recordsize<<"\n";
        file<<"totalSize:"<<newTable.totalSize<<"\n";
        file<<"records:"<<newTable.records<<"\n";
        file.close();
    }
    else
        cout<<"cant open catlog.txt";
}
void writeVectorToText(vector<string> allLines){
    fstream file;
    file.open("catlog.txt", ios::out);
    if(file.is_open()){
        for (int i = 0; i <allLines.size() ; i++) {
            file<<allLines[i]<<"\n";
        }
    }
    else{
        cout<<"cant open catlog for writing Insert";
    }

}

void writeInsertToCatlog(string tableName,vector <int> eachRowAndNumOfRecords){
    //cout<<"In catlog have to write to txt table is "<<tableName<<"values are"<<eachRowAndNumOfRecords[0]<<endl;
    string line;
    string deleteline;
    fstream file;
    vector<string> allLines;
    file.open("catlog.txt", ios::in | ios::out);
    if(file.is_open()){
        while(getline(file,line)){
           // cout<<"each line is sis isi s"<<line<<"Table name is "<<tableName<<endl;
            if (line.find("tableName:"+tableName) != std::string::npos) {
                allLines.push_back(line);
                getline(file,line);
                allLines.push_back(line);
                getline(file,line);
                allLines.push_back(line);
                getline(file,line);
              //  cout<<"Line is sis "<<line<<endl;
                if(line.find("recordsize")!=string::npos)
                {
              //      cout<<"in record size"<<endl;
                    deleteline=line;
                    string newLine ="recordsize:"+(std::to_string(eachRowAndNumOfRecords[0]));
                   // line.replace(line.find(line),line.length(),newLine);
              //      cout<< "newLine is "<<newLine<<endl;
                    allLines.push_back(newLine);
                }
                getline(file,line);
            //    cout<<"line toatal size"<<line;
                if(line.find("totalSize")!=string::npos)
                {
             //       cout<<"in totalSize size"<<endl;
                    deleteline=line;
                    string newLine ="totalSize:"+(std::to_string(eachRowAndNumOfRecords[0]*eachRowAndNumOfRecords[1]));
                   // line.replace(line.find(deleteline),deleteline.length(),"");
             //       cout<< "newLine is "<<newLine<<endl;
                    allLines.push_back(newLine);
                }
                getline(file,line);
                if(line.find("records:")!=string::npos)
                {
//                    cout<<"in records "<<endl;
                    string newLine ="records:"+(std::to_string(eachRowAndNumOfRecords[1]));
                    deleteline=line;
                    //line.replace(line.find(deleteline),deleteline.length(),"");
              //      cout<< "newLine is "<<newLine<<endl;
                    allLines.push_back(newLine);
                }
            }
            else{
                allLines.push_back(line);
            }
        }
        file.close();
        writeVectorToText(allLines);
    }
    else
        cout<<"cant open catlog.txt";
}
void writeCreate(string tableName, string query){
    string restOfQuery=split(query,'(')[1];
    string structureOftable;
    string primaryKey;
    vector<string> internalQuerie= commasSeperationInternalQuery(query);
    for (int i = 0; i < internalQuerie.size(); ++i) {
        if(internalQuerie[i].find("PRIMARY")!=std::string::npos){
            string temp=eraseSubStr(internalQuerie[i],"PRIMARY");
            primaryKey.append(eraseSubStr(temp,"KEY"));
        }
        else{
            structureOftable.append(internalQuerie[i]);
            if(i!=internalQuerie.size()-1)
                structureOftable.append(",");
        }
    }
    //cout<<"the structure of table is "<<structureOftable<<endl;
   // cout<<endl;
    TableClass newTable;
    newTable.tablename=tableName;
    newTable.columns=structureOftable;
    newTable.primary_key=primaryKey;
    newTable.records=0;
    newTable.recordsize=0;
    newTable.totalSize=0;
    writeObjToCatlog(newTable);

}

void writeInsert(){

}



