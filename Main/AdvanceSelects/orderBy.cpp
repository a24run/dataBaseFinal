//
// Created by a24run on 4/21/18.
//
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <algorithm>
#include "../headerFiles/actionFinder.h"
#include "../headerFiles/catlog.h"
#include "../headerFiles/BinaryReadWrite.h"

#include "../headerFiles/select.h"
#include "../headerFiles/orderBy.h"

vector<string> returnParamsOfQuery (string query,vector<string> tokens){
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
        vector<string> tableParams;
        tableParams.push_back(trim_copy(ourtableName));
        tableParams.push_back(trim_copy(selector));
        tableParams.push_back(trim_copy(finalWhereCondition));

        return tableParams;
    }
}

vector<vector<string>> outputOfOrder(vector<vector<string>> refinedData, string tableName, string selector){
    if(selector.find(",")!=string::npos){
        //cout<<"more than one selector";
        return  moreThanOneSelector(refinedData,tableName,selector);
    }
    else{
        // cout<<"Only one selector"<<endl;
       return oneSelector(refinedData,tableName,selector);
    }
}

vector<string> getColumnOrderBy (string where){
    //cout<<"where is "<<where<<endl;
    string tempOrderStatement = trim_copy(where);
    string columnDesc = eraseSubStr(where, "ORDER BY");
    vector<string> columnAndType;
    if(columnDesc.find("DESC")!=string::npos){
        string columnName = split(columnDesc,' ')[0];
        columnAndType.push_back(trim_copy(columnName));
        columnAndType.push_back("DESC");
        return columnAndType;
    }
    else
    {
        string columnName = split(columnDesc,';')[0];
        columnAndType.push_back(trim_copy(columnName));
        columnAndType.push_back("ASCE");
        return columnAndType;
    }
}

int getColumnNumber(string columns, string FindingColumn){
    vector<string> tempColumns = split(columns , ',');
    vector<string> tableColumns ;
    for(int index = 0; index < tempColumns.size(); index++){
        if(tempColumns[index].size() > 3 ){
            tableColumns.push_back(trim_copy(tempColumns[index]));
        }
    }

    for(int index = 0 ; index < tableColumns.size() ; index++){
        vector<string> tempEachColumn = split(tableColumns[index],' ');
        if(tempEachColumn[0]== FindingColumn){
            return index;
        }
        if(index == tableColumns.size()-1 && tempColumns[0] != FindingColumn){
            return 0;
        }
    }
}

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
    std::multimap<B,A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
                   flip_pair<A,B>);
    return dst;
}

vector<int> checkAndReturnArray(vector<string> typeofColumns, int columnNumber, vector<vector<string>> tableData){
    vector<int> indexesOfMap;
    if(trim_copy(typeofColumns[columnNumber]) =="INT"){
        map<int,int> mapSortGivenKeyData;
        for (int index =0; index < tableData.size(); index++){
          //  cout<<"value is "<<(tableData[index])[columnNumber]<<endl;
            mapSortGivenKeyData[index]=stoi((tableData[index])[columnNumber]);
        }
       // cout<<mapSortGivenKeyData.size()<<endl;
//        for(int index =0; index < mapSortGivenKeyData.size();index++){
//            cout<<mapSortGivenKeyData.<<endl;
//        }
        multimap<int,int> plzSort = flip_map(mapSortGivenKeyData);
        map<int, int>::iterator it;

        for ( it = plzSort.begin(); it != plzSort.end(); it++ )
        {
//            std::cout << it->first  // string (key)
//                      << ':'
//                      << it->second   // string's value
//                      << std::endl ;
            indexesOfMap.push_back(it->second);
        }
        return indexesOfMap;
    }
    else{
        map<int,string> mapSortStringGivenKeyData;
        for (int index =0; index < tableData.size(); index++){
            mapSortStringGivenKeyData[index]=(tableData[index])[columnNumber];
        }
       // cout<<mapSortStringGivenKeyData.size()<<endl;
        multimap<string ,int > stringSort = flip_map(mapSortStringGivenKeyData);
        map<string, int>::iterator it;

        for ( it = stringSort.begin(); it != stringSort.end(); it++ )
        {
//            std::cout << it->first  // string (key)
//                      << ':'
//                      << it->second   // string's value
//                      << std::endl ;
            indexesOfMap.push_back(it->second);
        }
        return indexesOfMap;
    }

}

vector<vector<string>> printOrderBy(vector<int> columnsToPrint, map<int,vector<string>> unSortedMap){
    vector<vector<string>> sortedVector;
    for(int index = 0; index<columnsToPrint.size() ; index++){
       sortedVector.push_back(unSortedMap[columnsToPrint[index]]);
    }
    return sortedVector;
}

vector< vector<string>> orderByStarter(string query,vector<string> tokens){
    //cout<<"order by "<<query<<endl;
    cout<<endl;
    vector<string> params = returnParamsOfQuery(query, tokens);
//    cout<<"table Name   "<<params[0]<<endl;
//    cout<<"Selector "<<params[1]<<endl;
//    cout<<"Where Condition  "<<params[2]<<endl;
//    vector<vector<string>> tableData = dataWithoutOrder(params[0], params[1]);
    vector<vector<string>> tableData = readFromTBL(params[0]);
//    cout<<"data is "<<endl;
//    pleasePrint(tableData);
    vector<string> columns = getSpecificLineOftable(params[0],"columns");
    //cout<<columns[0]<<" :   "<<columns[1]<<endl;
    vector<string> columnAndType = getColumnOrderBy(params[2]);
//    cout<<"column"<<columnAndType[0]<<endl;
//    cout<<"order "<<columnAndType[1]<<endl;
    vector<string> typeofColumns = getDataTypesVectorFromCatlog(params[0]);
    map<int,vector<string>> mapBeforeSortData;
    int columnNumber =  getColumnNumber(columns[1], columnAndType[0]);
    for (int index =0; index < tableData.size(); index++){
        mapBeforeSortData[index]=tableData[index];
    }
    vector<int> columnsToPrint =checkAndReturnArray(typeofColumns, columnNumber, tableData);
    vector<int> descData;
    for(int index = columnsToPrint.size()-1 ; index >= 0 ; index--){
        descData.push_back(columnsToPrint[index]);
    }
    vector<vector<string>> sortedData;
    if(columnAndType[1] == "DESC")
    {
        sortedData = printOrderBy(descData, mapBeforeSortData);

    }
    else if(columnAndType[1] == "ASCE"){
        sortedData = printOrderBy(columnsToPrint, mapBeforeSortData);

    }
    vector<vector<string>> finalData = outputOfOrder(sortedData, params[0], params[1]);
    return (finalData);
}

void orderByInitial(string query,vector<string> tokens){
    vector<vector<string>> sortedData  = orderByStarter(query,tokens);
    pleasePrint(sortedData);
}