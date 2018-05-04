//
// Created by a24run on 3/28/18.
//
#include <iostream>
using namespace std;
#include <vector>
#include "../headerFiles/actionFinder.h"
#include "../headerFiles/catlog.h"
#include "../headerFiles/BinaryReadWrite.h"

#include "../headerFiles/select.h"
#include "selectPrinter.h"

selectPrinter printer;

void pleasePrint(vector<vector<string>> allSolutions){
    cout<<"printing Data "<<endl;
    for(int i=0;i<allSolutions.size();i++){
        for(int j=0;j<allSolutions[i].size();j++)
        {
            cout<<allSolutions[i][j]<<"     ";
        }
        cout<<endl;
    }
}

char checkOperatorForWhere(string where){
    vector<char> operatorsForWhere;
    operatorsForWhere.push_back('=');
    operatorsForWhere.push_back('<');
    operatorsForWhere.push_back('>');
    for(int i=0; i<operatorsForWhere.size();i++){
        if(where.find(operatorsForWhere[i])!=string::npos)
            return operatorsForWhere[i];
    }

}

vector<string> subStringsWithoutDelimeter(string mainString, string delimiter){
    size_t pos = 0;
    std::string token;
    vector<string> split;
    while ((pos = mainString.find(delimiter)) != std::string::npos) {
        token = mainString.substr(0, pos);
        //std::cout << token << std::endl;
        string first=mainString.substr(0,pos);
        if(trim_copy(first).length()!=0)
            split.push_back(first);
        string second=mainString.substr(pos + delimiter.length(),mainString.length()-1);
        if(trim_copy(second).length()!=0)
            split.push_back(second);
        mainString.erase(0, pos + delimiter.length());
    }
    return split;
}

vector<vector<string>> oneSelector(vector<vector<string>> allData,string tableName,string selctor){
    //vector<vector<string>> allData=readFromTBL(tableName);
    vector<int> sizes=getDatasizeOfTable(tableName);
    int a;
    string b;
    if(selctor== "*")
        return printer.printer(allData);
    else{
       // cout<<"SELECT "<<selctor<<" FROM "<<tableName<<endl;
        vector<string> columns= getSpecificLineOftable(tableName, "columns");
        vector<string> eachColumn =split(columns[1],',');
        vector<int> ourColumn;
        int count=0;
        for (int i = 0; i < eachColumn.size(); ++i) {
            if(eachColumn[i].find(selctor)!=string::npos){
                ourColumn.push_back(i);
            }
            else
                count++;
        }
        if(count==eachColumn.size()){
            cout<<"COLUMN NOT FOUND"<<endl;
        }
        else
            return printer.printer(allData,ourColumn);
    }
}

vector<vector<string>> moreThanOneSelector(vector<vector<string>> allData,string tableName,string selector){
    //vector<vector<string>> allData=readFromTBL(tableName);
    vector<int> sizes=getDatasizeOfTable(tableName);

    vector<string> columns= getSpecificLineOftable(tableName, "columns");
    vector<string> eachColumn =split(columns[1],',');

    vector<string> selectors =split(selector,',');
    vector<int> ourColumns;
    int count=0;
    for (int i=0; i< selectors.size();i++){
        for (int j = 0; j < eachColumn.size(); j++) {
           // cout<<"checking"<<selectors[i]<<" catlog"<<eachColumn[j]<<endl;
            if(eachColumn[j].find(selectors[i])!=string::npos){
                ourColumns.push_back(j);
            }
            else
                count++;
        }
    }
    if(ourColumns.size()!=selectors.size()){
        cout<<"COLUMNS NOT FOUND"<<endl;
    }
    else
       return printer.printer(allData,ourColumns);
}

vector<vector<string>> whereSelector(vector<vector<string>> allData,string tableName,string selector, string where){
    char operation;
    char operatorForQuerey = checkOperatorForWhere(where);
    vector<int> sizes=getDatasizeOfTable(tableName);
    vector<string> printableData;
    if(selector== "*")
    {
        vector<string> columns= getSpecificLineOftable(tableName, "columns");
        vector<string> eachColumn =split(columns[1],',');
        string wherer = split(where,operatorForQuerey)[0];
        string comparer=split(where,operatorForQuerey)[1];
        int ourColumn=0;
        int count=0;
        for (int i = 0; i < eachColumn.size(); i++) {
            if(eachColumn[i].find(wherer)!=string::npos){
                ourColumn=i;
            }
            else
                count++;
        }
      //  cout<<"SELECT * FROM "<<tableName<<" WHERE "<<where<<endl;
        if(count==eachColumn.size()){
            cout<<"COLUMNS NOT FOUND"<<endl;
        }
        else{
          // cout<<"Columsn found"<<endl;
            vector<int> allRowMAtches;
            for (int i = 0; i < allData.size(); i++) {
                for (int j = 0; j < allData[i].size(); j++) {
                    if(j==ourColumn){
                      //  cout<<"comparer and value is "<<allData[i][j]<<"        "<<comparer<<endl;
                        //cout<<"less than "<<" "<<stoi(allData[i][j])<<"   "<<stoi(comparer) <<endl;
                        //   cout<<"operation is "<<operatorForQuerey<<endl;
                        if(operatorForQuerey=='='){
                            if(is_number(comparer)) {
                                if(is_number(allData[i][j]))
                                {
                                    if (stoi(allData[i][j]) == stoi(comparer))
                                        allRowMAtches.push_back(i);
                                }
                            }
                            else if(allData[i][j]==erasequotes(comparer)){
                                //cout<<"comparing these"<<allData[i][j]<<"   "<<comparer<<endl;
                                // cout<<"i is "<<i<<endl;
                                allRowMAtches.push_back(i);
                            }
                        }
                        else if(operatorForQuerey=='>'){

                            if(is_number(allData[i][j])) {
                                if (stoi(allData[i][j]) > stoi(comparer)) {
                              //      cout<<"plz xomparing"<<allData[i][j]<<"     "<<comparer<<endl;
                                    allRowMAtches.push_back(i);
                                }
                            }
                        }
                        else if(operatorForQuerey=='<'){
                            if(is_number(allData[i][j])){
                                // cout<<"is number"<<comparer<<endl;
                                if(stoi(allData[i][j])<stoi(comparer)){
                                    allRowMAtches.push_back(i);
                                }
                            }

                        }
                    }

                }
            }
           return printer.printer(allRowMAtches,allData);
        }
    }
    else{
       // cout<<"multipleSelectors "<<where<<endl;
      //  pleasePrint(moreThanOneSelector(allData,tableName,selector));
        vector<vector<string>> dataAfterWhere=whereSelector(allData,tableName,"*", where);
        //pleasePrint(dataAfterWhere);
     //   cout<<"multipleSelectors "<<where<<"selectors"<<selector<<"     "<<endl;
        return moreThanOneSelector(dataAfterWhere,tableName,selector);
    }
}
void doActionSelect(string tableName,string selector, string where){
    vector<vector<string>> allData=readFromTBL(tableName);
    if(trim_copy(where) ==";")
    {
        if(selector.find(",")!=string::npos){
            //cout<<"more than one selector";
           pleasePrint( moreThanOneSelector(allData,tableName,selector));
        }
        else{
           // cout<<"Only one selector"<<endl;
            pleasePrint(oneSelector(allData,tableName,selector));
        }
    }
    else{
       // cout<<"selector is "<<selector<<endl;
      // cout<<"wherer is "<<where<<endl;
        pleasePrint(whereSelector(allData,tableName,trim_copy(selector),trim_copy(where)));

    }
}

void selectAction(string query,vector<string> tokens){
    string ourtableName;
    vector<TableClass> alltables = returnAllTables();
    vector<string> tableNames;
    for (int i = 0; i < alltables.size(); i++) {
        tableNames.push_back(alltables[i].tablename);
    }
    int count=0;
    for (int j = 0; j < tableNames.size(); j++) {
        //cout<<"table name is "<<tableNames[j]<<endl;
        //cout<<"query is "<<query<<endl;
        if(query.find(" "+tableNames[j]+";")!=string::npos || query.find(" "+tableNames[j]+" ")!=string::npos){
            ourtableName=tableNames[j];
            break;
        }
        else
            count++;
    }
    //cout<<"count is "<<count<<"     "<<tableNames.size()<<endl;
    if(count == tableNames.size()){
        cout<<"Table dosent exist";
    }
    else{
       // cout<<"Table exists"<<ourtableName<<endl;
        string finalWhereCondition;
        string selectPart= subStringsWithoutDelimeter(query," "+ourtableName)[0];
        string ConditionPart=subStringsWithoutDelimeter(query," "+ourtableName)[1];

        string starFrom = subStringsWithoutDelimeter(selectPart,"SELECT ")[0];
        string selector = subStringsWithoutDelimeter(starFrom," FROM")[0];
       // cout<<selectPart<<"   "<<ConditionPart<<endl;
        if(ConditionPart.find("WHERE")!=string::npos){
            string WhereRemove =subStringsWithoutDelimeter(ConditionPart,"WHERE ")[0];
            finalWhereCondition =subStringsWithoutDelimeter(WhereRemove,";")[0];
            //cout<<"Final  Part is "<<finalWhereCondition<<endl;
        }
        else{
            finalWhereCondition=ConditionPart;
        }
       //cout<<"Table name "<<ourtableName<<"Query Selector is "<<selector<<"condition i s"<<finalWhereCondition<<endl;
        doActionSelect(ourtableName,selector,finalWhereCondition);
    }
}