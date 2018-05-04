//
// Created by a24run on 3/28/18.
//

#include <iostream>
using namespace std;
#include <vector>
#include "../headerFiles/actionFinder.h"
#include "../headerFiles/catlog.h"
#include "../headerFiles/BinaryReadWrite.h"

#include "../headerFiles/insert.h"

void printVector(vector<string> values){
    cout<<"printing vector data types"<<endl;
    for (int i = 0; i < values.size(); i++) {
        cout<<values[i]<<endl;
    }
}

void writeToCatlog(string table){
   // cout<<"in insert have to write to catlog"<<endl;
    vector <int> fromBinaryFile =eachRowAndnumRecordsTbl(table);
    writeInsertToCatlog(table,fromBinaryFile);
}

void insertValuestoTbl(string table , vector<string> input){
    //cout<<"proper Input"<<endl;
    writeToTBL(table , input);
}

vector<string> getDataTypesFromQuery(string columns){
    vector<string> tableColumnValues =split(columns,',');
    vector<string> dataTypes;
    for (int i = 0; i < tableColumnValues.size(); ++i) {
        if(tableColumnValues[i].find("'")!=string::npos){

            string toCalculate=trim_copy(tableColumnValues[i]);
          //  cout<<"value of char is "<<trim_copy((tableColumnValues[i]))<<"len"<<toCalculate.length()<<endl;
            string charAndLength=string("CHAR")+","+to_string(toCalculate.length()-2);
          //  cout<<"hehe"<<charAndLength<<endl;
            dataTypes.push_back(charAndLength);
        }
        else
            dataTypes.push_back("INT");
    }
    return dataTypes;
}

int isInputAccordingtoTable(string tablename, string query){
    vector<string> internalQuery = commasSeperationInternalQuery(query);
    string strInternalQuery;
    for (int i = 0; i < internalQuery.size(); i++) {
        strInternalQuery.append(internalQuery[i]);
        if(i!=internalQuery.size()-1)
            strInternalQuery.append(",");
    }
    //cout<<"insert internal Query is "<<strInternalQuery<<endl;
    vector<string> dataTypesOfquery=getDataTypesFromQuery(strInternalQuery);
    vector<string> CatlogdataTypes=getDataTypesVectorFromCatlog(tablename);
   // cout<<"query"<<endl;
   // printVector(dataTypesOfquery);
   // cout<<"catlog"<<endl;
 //   printVector(CatlogdataTypes);
    if(dataTypesOfquery.size()!=CatlogdataTypes.size())
        return 0;
    else{
        int count=0;
        for (int i = 0; i < dataTypesOfquery.size(); i++) {
            if(trim_copy(dataTypesOfquery[i])!=trim_copy(CatlogdataTypes[i]))
            {
                //cout<< trim_copy(dataTypesOfquery[i])<<" "<<trim_copy(CatlogdataTypes[i])<<endl;
                if(dataTypesOfquery[i].find("CHAR")!=string::npos && CatlogdataTypes[i].find("CHAR")!=string::npos)
                {
                    int numQuery = std::stoi( split(dataTypesOfquery[i],',')[1]);
                    int numCatlog = std::stoi( split(CatlogdataTypes[i],',')[1]);
                   // cout<<"num qu"<<numQuery<<" "<<"num catlog"<<numCatlog<<endl;
                    if(numCatlog>=numQuery)
                    {
                        count++;
                    }
                    else {
                        return 0;
                    }
                }
                else
                    return 0;

            }
            else
                count++;
        }
        //cout<<"count is "<<count<<endl;
        if(count==dataTypesOfquery.size())
            return 1;
        else
            return 0;
    }

}

void insertAction(string query,vector<string> tokens){
    string tableName = tokens[2];
    if(checkTableExists(tableName)==1){
        if(isInputAccordingtoTable(tableName, query)==0)
            cout<<"Improper Input"<<endl;
        // table exists write into tbl file
        else
        {
            insertValuestoTbl(tableName , commasSeperationInternalQuery(query));
            writeToCatlog(tableName);
            cout<<"ONE ROW INSERTED SUCCESSFULLY"<<endl;
        }
    }
    else{
        cout<<" Table "<<tableName<<" Does not exists"<<endl;
    }
}