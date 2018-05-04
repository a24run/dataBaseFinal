#include <iostream>
using namespace std;
#include <stdlib.h>
#include <string>
#include <vector>

// include the sql parser
#include "src/SQLParser.h"

// contains printing utilities
#include "src/sqlhelper.h"

//Action Finder
#include "Main/headerFiles/actionFinder.h"

#include "Main/input/input.h"

// Catlog file
#include "Main/headerFiles/catlog.h"
// Managing Files
#include "Main/headerFiles/charTextManage.h"
int main(int argc, const char **argv) {
    createCatlog();
    string inputVlaues[argc];
    string initialQuery;
    for (int i = 1; i < argc ; i++){
        inputVlaues[i] = argv[i];
        initialQuery += argv[i];
        initialQuery += " ";
    }
    string senderr= argv[1];
    //This is the input
    vector<string> inputQueries =input(argc,senderr);
    for (auto &i : inputQueries)
        for (auto &j : i)
        {
            j = toupper(j);
        }
//    for (std::size_t i = 0; i < inputQueries.size(); i++)
//    {
//        inputQueries[i]+=";";
//        cout << inputQueries[i] << endl;
//    }
    for (int j = 0; j < inputQueries.size(); j++) {
        //cout<<"Calling inputs "<<inputs.size()<<endl;
        string QuerieForParser;
       // cout<<"bEFORE mANAGE "<<QuerieForParser<<endl;
       // cout<<"input is "<<inputQueries[j]<<endl;
        if(inputQueries[j].find("SHOW")==string::npos)
        {
            if(inputQueries[j].find("CREATE")!=string::npos)
                QuerieForParser=manageForParser(inputQueries[j]);
            else
                QuerieForParser=inputQueries[j];
            cout<<QuerieForParser<<endl;

            //Calling parser
            std::string query = argv[1];
            hsql::SQLParserResult* result = hsql::SQLParser::parseSQLString(QuerieForParser);
            // RESULT Passing to Do Action
            if(result->isValid())
                findDoaction(inputQueries[j]);
            else
                cout<<"Error in query";
        }
        else
            findDoaction(inputQueries[j]);
    }
}
