//
// Created by a24run on 3/27/18.
//
#include <iostream>

using namespace std;

#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

#include "headerFiles/actionFinder.h"
#include "headerFiles/create.h"
#include "headerFiles/select.h"
#include "headerFiles/insert.h"
#include "headerFiles/show.h"
#include "headerFiles/join.h"
#include "headerFiles/orderBy.h"
#include "headerFiles/groupBy.h"
#include "headerFiles/joinON.h"
template<typename Out>
void split(const string &s, char delim, Out result) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}
//Erases the sub string from main string and returns the rest
string eraseSubStr(std::string & mainStr, const std::string & toErase) {
    // Search for the substring in string
    size_t pos = mainStr.find(toErase);
    if (pos != std::string::npos)
        mainStr.erase(pos, toErase.length());// If found then erase it from string
    return mainStr;
}

//GIves the Internal query as vector
vector<string> commasSeperationInternalQuery(string query){
    vector<string> solution;
    vector<string> values=split(query,',');
    //cout<<"name and 1st param"<<values[0]<<endl;
    string temp =split(values[0],'(')[0];
    temp+='(';
    // have to remove temp from values[0]
    solution.push_back(eraseSubStr(values[0],temp));
    for (int i = 1; i <= values.size()-2; ++i) {
        solution.push_back(values[i]);
    }
    string finalTemp=");";
    //cout<<"final temp is "<<finalTemp<<endl;
    solution.push_back(eraseSubStr(values[values.size()-1],finalTemp)); // This is fucked but works

    return solution;
}

//Check IF number of not
bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

//Erase 1st and last '
string erasequotes(string input){
    input.erase( 0, 1 ); // erase the first character
    input.erase( input.size() - 1 ); // erase the last character
    //cout<<"after erased "<<input<<endl;
    return input;
}

// Trims the values fromm front and back and sends the string
// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
}
// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}
// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}
// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}
// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}
// trim from both ends (copying)
string trim_copy(std::string s) {
    trim(s);
    return s;
}

void findDoaction(string query){
    //cout<<"string is "<<query<<endl;
    string sentence = query;
    vector <string> tokens = split(query, ' ');
    if(sentence.find("SELECT")!=string::npos && sentence.find("JOIN")!=string::npos && sentence.find("WHERE")==string::npos){
        joinStatement(sentence);
    }
    else if(sentence.find("SELECT")!=string::npos && sentence.find("JOIN")!=string::npos && sentence.find("WHERE")!=string::npos){
        joinOnStatement(sentence);
    }
    else if(sentence.find("SELECT")!=string::npos && sentence.find("ORDER BY")!=string::npos && sentence.find("GROUP BY")==string::npos)
    {
        orderByInitial(query,tokens);
    }
    else if(sentence.find("SELECT")!=string::npos && sentence.find("GROUP BY")!=string::npos)
    {
        groupByStarter(query,tokens);
    }
    else if(tokens[0]=="CREATE"){
        cout<<"Create Statement"<<query<<endl;
        createAction(query,tokens);
    }
    else{
        if(tokens[0]=="SELECT"){
            cout<<"Select Statement"<<endl;
            selectAction(query,tokens);
        }
        else if(tokens[0]=="INSERT"){
            cout<<"Insert Statement"<<endl;
            insertAction(query,tokens);
        }
        else if(tokens[0]=="SHOW"){
            cout<<"Show Statement"<<endl;
            show(query,tokens);
        }
        else{
            cout<<"Please check the query"<<endl;
        }
    }

}
