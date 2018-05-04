//
// Created by a24run on 4/6/18.
//

#include "selectPrinter.h"

//void pleasePrint(vector<vector<string>> allSolutions){
//    for(int i=0;i<allSolutions.size();i++){
//        for(int j=0;j<allSolutions[i].size();j++)
//        {
//            cout<<allSolutions[i][j]<<"     ";
//        }
//        cout<<endl;
//    }
//
//}
vector<vector<string>> selectPrinter::printer(vector<vector<string>> allData) {
    vector<vector<string>> allSolutionValues;
    for (int i = 0; i < allData.size(); i++) {
        allSolutionValues.push_back(allData[i]);
        return (allData);
    }
}

vector<vector<string>> selectPrinter::printer(vector<vector<string>>allData, int specificColumn) {
    vector<vector<string>> allSolutionValues;
    for (int i = 0; i < allData.size(); i++) {
        for(int j =0 ;j<allData[i].size();j++){
            if(j == specificColumn)
            {
                vector<string>temp;
                temp.push_back(allData[i][j]);
                allSolutionValues.push_back(temp);
            }
        }
    }
    return (allSolutionValues);
}

vector<vector<string>> selectPrinter::printer(vector<vector<string>> allData, vector<int> columnsToPrint) {
    vector<vector<string>> allSolutionValues;
    for(int i=0 ;i<allData.size();i++){
        vector<string> temp;
        for (int j = 0; j < allData[i].size(); j++) {
            for (int k = 0; k < columnsToPrint.size(); k++) {
                if(columnsToPrint[k]==j){
                    temp.push_back(allData[i][j]);
                }
            }
        }
        allSolutionValues.push_back(temp);
    }
    return (allSolutionValues);
}

vector<vector<string>> selectPrinter::printer(vector<int> allRowMAtches, vector<vector<string>> allData) {
    vector<vector<string>> allSolutionValues;
    for (int i = 0; i < allData.size(); i++) {
        vector<string>temp;
        for(int k=0; k<allRowMAtches.size() ;k++){
            if(allRowMAtches[k]==i){
                for (int j = 0; j < allData[i].size(); j++) {
                    temp.push_back(allData[i][j]);
                }
            }
        }
        allSolutionValues.push_back(temp);
    }
    return (allSolutionValues);
}

vector<vector<string>> selectPrinter::printer(vector<vector<string>> moreThanOneSelector, vector<vector<string>> whereSelectorResult) {
    vector<vector<string>> allSolutionValues;
    for (int i = 0; i < whereSelectorResult.size(); i++) {
        vector<string>temp;
        for(int k=0; k<moreThanOneSelector.size() ;k++){
            if(moreThanOneSelector[k]==whereSelectorResult[i]){

            }
        }
        allSolutionValues.push_back(temp);
    }
    return (allSolutionValues);
}




