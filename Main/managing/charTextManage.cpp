//
// Created by a24run on 3/29/18.
//

#include <iostream>
using namespace std;
#include <vector>

#include "../headerFiles/actionFinder.h"

string changeText(vector< string> query, string originalText, string changeText){
    string newQuery="";
    for( int i = 0; i<query.size(); i++){
        if(query[i].find(originalText)!= string::npos)
            newQuery.append(changeText);
        else
            newQuery.append(query[i]+" ");
    }
    return newQuery;
}
string checkChar(string query){
    if(query.find('CHAR') != string::npos)
    {
        vector<string> subQueries= split(query,' ');
        return changeText(subQueries ,"CHAR", "TEXT");
    }
    else
        return query;
}
string checkPrimaryKey(string value){
    if(value.find("PRIMARY KEY") != string::npos)
    {
       // cout<<("value found ")<<value<<endl;
        return "";
    }
    else
        return value;
}
string splitReturnStr(string query,char Operator,int selector){
    vector<string> subQuery= split(query,Operator);
    string content="";
    for(int i=selector;i< subQuery.size();i++){
        content.append(subQuery[i]);
    }
    return content;
}

string charText(string query){
    string parserQuerie=split(query,'(')[0];
    string removedBracket=splitReturnStr(query,'(',1);
    parserQuerie.append("(");
    string removedOtherB = splitReturnStr(removedBracket,')',0);
    vector<string> commaSeperator= split(removedOtherB,',');
    vector<string> finalInternalQuerie;
    for(int i=0;i< commaSeperator.size();i++){
        if(commaSeperator[i].find(";") != std::string::npos)
            finalInternalQuerie.push_back(split(commaSeperator[i],';')[0]);
        else
            finalInternalQuerie.push_back(commaSeperator[i]);
    }
    for(int i=0;i<finalInternalQuerie.size();i++){
        string preChanged=finalInternalQuerie[i];

        finalInternalQuerie[i]=checkChar(trim_copy(finalInternalQuerie[i]));
        //cout<<"plz "<<finalInternalQuerie[i]<<endl;
        finalInternalQuerie[i]=checkPrimaryKey(trim_copy(finalInternalQuerie[i]));
      //  cout<<"plz "<<finalInternalQuerie[i]<<endl;


        if(preChanged.find("PRIMARY") != std::string::npos);
        else
        {
            parserQuerie.append(finalInternalQuerie[i]+" ");
            if(i!=finalInternalQuerie.size()-1)
                parserQuerie.append(",");
        }
    }
    if(parserQuerie[parserQuerie.size()-1]==','){
        parserQuerie[parserQuerie.size()-1]=' ';
    }
    parserQuerie.append(");");
    return parserQuerie;
}
string manageForParser(string query){
     return charText(query);
}
