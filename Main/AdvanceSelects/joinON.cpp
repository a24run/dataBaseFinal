//
// Created by a24run on 5/3/18.
//
#include <iostream>
#include <vector>
using namespace std;

#include "../headerFiles/actionFinder.h"
#include "../headerFiles/catlog.h"
#include "../headerFiles/BinaryReadWrite.h"
#include "../headerFiles/select.h"
#include "../output/selectPrinter.h"
#include "../headerFiles/join.h"
#include "../headerFiles/joinON.h"

vector< string> tempErase(std::string & mainStr, const std::string & toErase) {
    vector<string> splitWhere;
    string first,second;
    // Search for the substring in string
    size_t pos = mainStr.find(toErase);
    int total,position,deletesize;
    total= mainStr.length();
    position = pos;
    deletesize = total - position;
    //cout<<mainStr.length()<<"   "<<toErase.length()<<"  "<<pos<<endl;
    if (pos != std::string::npos)
    {   string tempString = mainStr;
        second = tempString.erase(0,pos+toErase.length());
        first = mainStr.erase(pos, total-pos);// If found then erase it from string
        first= trim_copy(first).append(";");
    }
    //cout<<"first"<<first<<"       second"<<second<<endl;
    splitWhere.push_back(first);
    splitWhere.push_back(second);
    return splitWhere;
}

void joinOnStatement(string query){
    vector<string> combibned = tempErase(query,"WHERE");
    string normalJoin = combibned[0];
    string whereCondition = combibned[1];
    //cout<<"normal string is"<<normalJoin<<endl;
    joinStatement(normalJoin);
}