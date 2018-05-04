//
// Created by a24run on 4/6/18.
//
#include <iostream>
#include <vector>
using namespace std;

#include "../headerFiles/actionFinder.h"
#include "../headerFiles/catlog.h"
#include "../headerFiles/BinaryReadWrite.h"
#include "../headerFiles/select.h"
#include "selectPrinter.h"

vector<string> returnColumnNumbers(vector<vector<string>> data){
    vector<string> postions;
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            postions.push_back(data[i][j]);
        }
    }
    return postions;
}
void printer (vector<int> tablesToPrint,vector<vector<string>>tableData){
    for (int k = 0; k < tableData.size(); ++k) {
        if(k==tablesToPrint[k])
        {
            for (int l = 0; l < tableData[k].size(); l++) {
                cout<<tableData[k][l]<<"    ";
            }
        }
        cout<<endl;
    }
}

void tablePrinter(vector<vector<string>> tableData , int whatNotToPrint){
    for(int i=0; i<tableData.size(); i++){
        for(int j=0;j<tableData[i].size();j++){
            if(j!=whatNotToPrint)
                cout<< tableData[i][j]<<"      ";
        }
    }
}

void newPrinterForLogicJoin(vector<vector <int>> columnsToPrint, vector<vector<string>> tableOneData, vector<vector<string>> tableTwoData , int indexOncolumnOfSecondTable ){
    for(int i=0;i< columnsToPrint.size();i++){

           // cout<<columnsToPrint[i][j];
            vector<string> tempTableOne = tableOneData[columnsToPrint[i][0]];
            vector<string> tempTableTwo = tableTwoData[columnsToPrint[i][1]];
            for( int k =0 ;k<tempTableOne.size();k++){
                cout<<tempTableOne[k]<<"    ";
            }
            for( int k =0 ;k<tempTableTwo.size();k++){
                if(k!=indexOncolumnOfSecondTable)
                    cout<<tempTableTwo[k]<<"    ";
            }
            cout<<endl;

        cout<<endl;
    }
}

int findColumnNumber(string tableName,string ColumnName){
    string columns = getSpecificLineOftable(tableName,"columns")[1];
    vector<string> columnsSplit = split(columns,',');
    for(int i=0;i<columnsSplit.size();i++){
        if(columnsSplit[i].find(ColumnName)!=string::npos)
            return i;
    }
}

void joinStatement(string query){
    string ourtableName;
    vector<TableClass> alltables = returnAllTables();
    vector<string> tableNames;
    for (int i = 0; i < alltables.size(); i++) {
        tableNames.push_back(alltables[i].tablename);
    }
    int count=0;
    string avoidTableConfusion = subStringsWithoutDelimeter(query,"JOIN")[0];
    for (int j = 0; j < tableNames.size(); j++) {
        //cout<<"table name is "<<tableNames[j]<<endl;
        //cout<<"query is "<<query<<endl;
        if(avoidTableConfusion.find(" "+tableNames[j]+";")!=string::npos || avoidTableConfusion.find(" "+tableNames[j]+" ")!=string::npos){
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
        //cout<<"Table exists"<<ourtableName<<endl;
        string finalWhereCondition;
        string selectPart= subStringsWithoutDelimeter(query," "+ourtableName)[0];
        string ConditionPart=subStringsWithoutDelimeter(query," "+ourtableName)[1];

        string starFrom = subStringsWithoutDelimeter(selectPart,"SELECT ")[0];
        string selector = subStringsWithoutDelimeter(starFrom," FROM")[0];
         cout<<"select part is "<<selectPart<<"   condition is "<<ConditionPart<<endl;
        if(ConditionPart.find("WHERE")!=string::npos){
            string WhereRemove =subStringsWithoutDelimeter(ConditionPart,"WHERE ")[0];
            finalWhereCondition =subStringsWithoutDelimeter(WhereRemove,";")[0];
            //cout<<"Final  Part is "<<finalWhereCondition<<endl;
        }
        else{
            finalWhereCondition=ConditionPart;
        }
        //Removed semicolumn
        finalWhereCondition=subStringsWithoutDelimeter(finalWhereCondition,";")[0];
      //  cout<<"final where is "<<finalWhereCondition<<endl;
        string secondTable,secondTableWithJoin;
        string conditionJoin;
        secondTableWithJoin=subStringsWithoutDelimeter(finalWhereCondition,"ON")[0];
        conditionJoin=trim_copy(subStringsWithoutDelimeter(finalWhereCondition,"ON")[1]);
        secondTable=trim_copy(subStringsWithoutDelimeter(secondTableWithJoin,"JOIN")[0]);
       // cout<<"first table "<<ourtableName<<"second table is "<<secondTable<<endl;
       // cout<<"condition is "<<conditionJoin<<endl;
        string firstTableCondition, secondTableCondition;
        firstTableCondition = trim_copy(subStringsWithoutDelimeter(conditionJoin,"=")[0]);
        secondTableCondition = trim_copy(subStringsWithoutDelimeter(conditionJoin,"=")[1]);
       // cout<<"first table condition"<<firstTableCondition<<endl;
        //cout<<"second table condition"<<secondTableCondition<<endl;
        string ColumnsONfirstTable = trim_copy(subStringsWithoutDelimeter(firstTableCondition,".")[1]);
        string ColumnsONSecondTable= trim_copy(subStringsWithoutDelimeter(secondTableCondition,".")[1]);
        //cout<<"firs condition column"<<ColumnsONfirstTable<<endl;
        //cout<<"second condition column"<<ColumnsONSecondTable<<endl;
       // cout<<"Table name "<<ourtableName<<"Query Selector is "<<selector<<"condition i s"<<finalWhereCondition<<endl;
        //doActionSelect(ourtableName,selector,finalWhereCondition);
        if(checkTableExists(ourtableName)+checkTableExists(secondTable)!=2){
            cout<<"Table Does not Exist"<<endl;
        }
        else{
           // cout<<"table existssadadad"<<endl;
            vector<vector<string>> firstTableData=readFromTBL(ourtableName);
            vector<vector<string>> tableOneCOlumns= oneSelector( firstTableData, ourtableName, ColumnsONfirstTable);
            vector<vector<string>> secondTableData=readFromTBL(secondTable);
            vector<vector<string>> tableTwoCOlumns=oneSelector( secondTableData, secondTable, ColumnsONSecondTable);
          //cout<<"CALLINg POSITIONS"<<endl;
            vector<string> tableOneColumnsFinal = returnColumnNumbers(tableOneCOlumns);
            vector<string> tableTwoColumnsFinal = returnColumnNumbers(tableTwoCOlumns);
         //   cout<<"GOT POSITIONS"<<endl;
            vector<int> tableOneRowsToPrint;
            vector<int> tableTwoRowsToPrint;
        // cout<<"checking    "<<tableOneColumnsFinal.size()<<endl;
            vector <vector<int>> columnAB;
            for(int i=0;i<tableOneColumnsFinal.size();i++){
                for (int j = 0; j < tableTwoColumnsFinal.size(); j++) {
                  //  cout<<tableOneColumnsFinal[i]<<" check here "<<tableTwoColumnsFinal[j]<<endl;
                    if(tableOneColumnsFinal[i]==tableTwoColumnsFinal[j]){
                        vector<int> tempColumns;
                        tempColumns.push_back(i);
                        tempColumns.push_back(j);
                        columnAB.push_back(tempColumns);
                        tableOneRowsToPrint.push_back(i);
                        tableTwoRowsToPrint.push_back(j);
                    }
                }
            }
            int indexOncolumnOfSecondTable = findColumnNumber(secondTable,ColumnsONSecondTable);
          //  cout<<"chek 1"<<tableOneRowsToPrint.size()<<endl;
           //  cout<<"chek 2"<<tableTwoRowsToPrint.size()<<endl;
           // printer (tableOneRowsToPrint,firstTableData);
            //printer (tableTwoRowsToPrint,secondTableData);
            newPrinterForLogicJoin(columnAB,firstTableData,secondTableData,indexOncolumnOfSecondTable);
        }
    }
}

