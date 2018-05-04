//
// Created by a24run on 3/31/18.
//
#include <iostream>
#include <vector>
#include<fstream>
#include <string.h>

using namespace std;
#include "../headerFiles/actionFinder.h"
#include "../headerFiles/catlog.h"

vector <int> eachRowAndnumRecordsTbl(string tableName){          // each record , number of record
    vector<int> sizes = getDatasizeOfTable(tableName);
    int eachRowSize=0;
    streampos size;
    for(int i=0;i<sizes.size();i++){
        eachRowSize+=sizes[i];
    //    cout<<"adding sizes "<<eachRowSize<<endl;
    }
    ifstream file(tableName.append(".tbl"),ios::ate | ios::binary  );
    if(file.is_open()){
        size = file.tellg();
        //cout<<"table name is "<<tableName+".tbl"<<"size"<<size<<endl;
        file.close();
    }
    else{
        cout << "Unable to open BINARY file";
    }
    int number =size/eachRowSize;
    vector<int> data;
    data.push_back(eachRowSize);
  //  cout<<"each row size is "<<eachRowSize<<endl;
  //  cout<<"number of querieds are "<<number<<endl;
    data.push_back(number);
    return data;
}


void writeToTBL(string tableName, vector<string> input){
    //cout<<"table name is "<<tableName<<endl;
    vector<int> sizes = getDatasizeOfTable(tableName);
    fstream Binfile(tableName+".tbl", ios::out | ios::app | ios::binary  );
    if (Binfile.is_open())
    {
        for (int i = 0; i <input.size() ; i++) {
            if(is_number(trim_copy(input[i]))){
                int a =stoi(input[i]);
                //cout<<"input is "<<a<<"size of input is "<< sizeof(a)<<"   "<<sizes[i]<<endl;
                Binfile.write((char*) &a, sizes[i]);
            }
            else{
                //cout<<"is string"<<input[i];
                string value= trim_copy(input[i]);
                value = erasequotes(value);
               // cout<<"value is "<<value<<"size is "<<value.size()<<endl;
                int n = value.length();
                char char_array[n+1];
                strcpy(char_array, value.c_str());
                //char *val = value.c_str();
                //const char *haha;
               // cout<<"input is "<<val<<"size of imput i s"<< sizeof(val)<<"   "<<sizes[i]<<endl;
                Binfile.write(char_array, sizes[i]);
            }
        }
        Binfile.close();
        //Write to catlog
        //writeInsert(tableName);
    }
    else
        cout<<"Cant open .tbl file"<<endl;
}





