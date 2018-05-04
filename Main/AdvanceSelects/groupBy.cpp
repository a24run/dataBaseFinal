//
// Created by a24run on 4/23/18.
//
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include "../headerFiles/actionFinder.h"

#include "../headerFiles/select.h"
#include "../headerFiles/orderBy.h"
#include "../headerFiles/groupBy.h"
#include "../headerFiles/catlog.h"

string removeOrderby(string basic_string);

vector<string> removeAggregatorReturnAll(string columnWithAggregator){
    vector<string> allColumns;
    vector<string> temp = split(columnWithAggregator,',');
    for(int index =0; index < temp.size(); index ++){
        allColumns.push_back(trim_copy(temp[index]));
    }
    return allColumns;
}

string removeOrderby(string groupColumn) {
    //cout<< "remove order BY"<<groupColumn<<endl;
    string temp = split(eraseSubStr(groupColumn,"ORDER BY"),' ')[0];
    return temp;
}
void groupByStarter(string query,vector<string> tokens){
    vector<string> params = returnParamsOfQuery(query , tokens);
//    for(int i =0 ; i< params.size() ; i ++){
//        cout<<params[i]<<endl;
//    }
    string tableName = params[0];
    vector<string> allColumnsWithAggregator= removeAggregatorReturnAll(params[1]);
    string groupColumn = split(eraseSubStr(params[2],"GROUP BY "),';')[0];
    //cout<<"group column is "<<groupColumn<<endl;
    if(groupColumn.find("ORDER BY") !=string::npos){
        groupColumn = removeOrderby(groupColumn);
    }

    string  aggregator;
    vector<string> allColumnsWithoutAggregator;

    for( int index =0 ; index< allColumnsWithAggregator.size(); index++){
        if(allColumnsWithAggregator[index].find("SUM") == string::npos){
            allColumnsWithoutAggregator.push_back(allColumnsWithAggregator[index]);
        }
        else{
            string temp = trim_copy(eraseSubStr(allColumnsWithAggregator[index],"SUM"));
            temp = eraseSubStr(temp,"(");
            temp = eraseSubStr(temp,")");
          //  cout<<"temp is "<<trim_copy(temp)<<endl;
            allColumnsWithoutAggregator.push_back(temp);
            aggregator = temp;
        }
    }
    string queryIntput;
    for(int index=0; index< allColumnsWithoutAggregator.size(); index++){
        if(index != allColumnsWithoutAggregator.size()-1){
            queryIntput+= allColumnsWithoutAggregator[index];
            queryIntput+=" ,";
        }
        else
            queryIntput+= allColumnsWithoutAggregator[index];
    }
    string orderByQuery = "SELECT "+queryIntput+ " FROM "+tableName +" ORDER BY "+groupColumn;
   // cout<<"orderByQuery "<<orderByQuery<<endl;

    vector<string> columns = getSpecificLineOftable(params[0],"columns");
    vector<string> columnsFromTable = split(columns[1],',');
    int groupIndex, aggregatorIndex;

    for( int index=0; index < columnsFromTable.size(); index++ ){
        if(trim_copy(columnsFromTable[index]) !=""){
            if(columnsFromTable[index].find(groupColumn)!=string::npos){
                groupIndex=index;
            }
            if(columnsFromTable[index].find(aggregator)!=string::npos){
                aggregatorIndex=index;
            }
        }
    }
    int groupDoubleIndex, aggregatorDoubleIndex;
    if(groupIndex < aggregatorIndex){
        groupDoubleIndex=0;
        aggregatorDoubleIndex=1;
    } else{
        groupDoubleIndex=1;
        aggregatorDoubleIndex=0;
    }
    vector<vector<string>> sortedData  = orderByStarter(orderByQuery,tokens);
   // pleasePrint(sortedData);
    vector<string> fucker;
    set<string> first;
    map<string,int> groupData;
    for (int index =0; index < sortedData.size(); index++){
        int intialLength =first.size();
        string chut =(sortedData[index])[groupDoubleIndex];
        first.insert(chut);
        if(first.size()>intialLength){
            fucker.push_back(chut);
            groupData[chut]= stoi((sortedData[index])[aggregatorDoubleIndex]);
        }
        else{
            groupData[chut] = groupData[chut]+ stoi((sortedData[index])[aggregatorDoubleIndex]);
        }
    }
   cout<<columnsFromTable[groupIndex] <<"          SUM "<<columnsFromTable[aggregatorIndex]<<endl;

    for(int index = 0 ; index < fucker.size() ; index ++){
        cout<<fucker[index]<<"          "<< groupData[fucker[index]] <<endl;
    }

}

