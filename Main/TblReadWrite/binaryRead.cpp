//
// Created by a24run on 4/5/18.
//
#include <iostream>
#include <vector>
#include<fstream>
#include <string.h>
using namespace std;
#include "../headerFiles/actionFinder.h"
#include "../headerFiles/catlog.h"
#include "../headerFiles/BinaryReadWrite.h"

vector<vector<string>> readFromTBL(string tableName){
    int data;
    const char* ar;
    int sizeOfeachQuery=0;
    vector<int> sizes=getDatasizeOfTable(tableName);
    TableClass table = returnTable(tableName);
    for (int i = 0; i < sizes.size(); i++) {
        sizeOfeachQuery+=sizes.size();
    }
    long size=table.totalSize;
    ifstream File(tableName+".tbl",ios::in | ios::binary);
    vector<vector<string>> allRowData;
    int reader=0;

    if(File.is_open()){
     //   cout<<"file is open"<<endl;
        File.seekg(0);
        while(reader<size){
            vector<string> blocksOfData;
            for (int i = 0; i < sizes.size(); i++) {
                if(sizes[i]==4)
                {
                    File.read ((char *)&data, sizes[i]);
                 //   cout<<"data iss "<<data<<endl;
                    blocksOfData.push_back(to_string(data));
                }
                else if(sizes[i]!=4)
                {
                     char* buf =new char[sizes[i]];
                     File.read (buf, sizes[i]);
                    string plz(buf);
                    delete [] buf;
                    //cout<<plz<<endl;
                    blocksOfData.push_back(plz);
                }
                reader+=sizes[i];
            }
            allRowData.push_back(blocksOfData);
        }
        File.close();
        //cout<<"queries are "<< blocksOfData.size()<<endl;
        return allRowData;
    }
    else{
        cout<<"cant open"<<tableName<<".tbl file "<<endl;
    }
}
