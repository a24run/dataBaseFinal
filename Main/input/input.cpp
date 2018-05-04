#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;
#include <vector>

#include "../headerFiles/actionFinder.h"
#include "input.h"

vector<string> input  (int numInputs, string inputs) {
    string name;
    //cout<<inputs<<endl;

    string line;
    string inputArgument = inputs;
    vector<string> quiries;
    ifstream script(inputArgument);
    string sqlQuery = "";
    string query = "";

    if (inputArgument.find("script") != string::npos)
    {
        char *batchFileName = strtok((char *) inputArgument.c_str(), "=");
        batchFileName = strtok(NULL, "=");
        if (batchFileName == NULL)
        {
            cout << "No Batch FileName Given" << endl;
            //return 0;
        } else {
            ifstream iput(batchFileName);
            if (iput.is_open()) {

                while (getline(iput, line, ';')) {
                    for (string::size_type i = 0; i < line.length(); ++i) {
                        if (isspace(line[i])) {
                            line[i] = ' ';
                        }
                    }
                    line.append(";");
                    cout<<"line is"<<line<<endl;
                    quiries.push_back(trim_copy(line));
                }
                quiries.erase(quiries.end() - 1);
                return quiries;
            } else {
                cout << "error opening file";
            }
        }
    }
    else
    {
        //cout << "inside else" << endl;
        while (inputArgument.length() > 0)
        {

            string sqlQueryInput = "";

            for (string::size_type i = 0; i < inputArgument.length(); ++i) {
                sqlQueryInput += toupper(inputArgument[i]);
            }
            // cout << sqlQueryInput << endl;

            size_t eachQueryBreak = sqlQueryInput.find(';');

            if (eachQueryBreak != string::npos) {

                string query = sqlQueryInput.substr(0, eachQueryBreak+1);
                quiries.push_back(query);
                return quiries;
            }
            else
            {
                cout << "ERROR: " << sqlQueryInput << " is not executed. No semicolon found at the end of statement." << endl;
                return {};
            }
        }
    }
}