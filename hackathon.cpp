#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>
#include"json.hpp"
using namespace std;
using json=nlohmann::json;

long long convertToDecimal(const string& numberInBase,int base){
    long long decimalValue=0;
    for(char digit:numberInBase){
        int digitValue;
        if(isdigit(digit))
            digitValue=digit - '0';
        else
            digitValue = tolower(digit)-'a'+10;
        decimalValue = decimalValue*base+digitValue;
    }
    return decimalValue;
}

double findConstantTerm(const vector<double>& xList, const vector<double>& yList){
    double constantTerm=0.0;
    int totalPoints=xList.size();
    for(int i=0;i<totalPoints;i++){
        double currentTerm=yList[i];
        for(int j=0;j<totalPoints;j++){
            if(j!=i){
                currentTerm*= (0.0-xList[j]) / (xList[i]-xList[j]);
            }
        }
        constantTerm+= currentTerm;
    }
    return constantTerm;
}

int main(){
    ifstream inputFile("testcase2.json");
    if(!inputFile.is_open()){
        cerr<<"Canoot open json file!"<<endl;
        return 1;
    }

    json inputData;
    inputFile >> inputData;
    inputFile.close();

    int totalRoots = inputData["keys"]["n"];
    int minimumRoots = inputData["keys"]["k"];

    vector<double> xValues;
    vector<double> yValues;

    for(auto element=inputData.begin(); element!=inputData.end(); ++element){
        if(element.key()=="keys") {
            continue;
        }
        
        int xValue=stoi(element.key());
        int baseOfY=stoi(element.value()["base"].get<string>());
        string yEncoded=element.value()["value"];
        long long yValue=convertToDecimal(yEncoded,baseOfY);
        xValues.push_back(xValue);
        yValues.push_back(yValue);
    }

    if(xValues.size()>minimumRoots){
        xValues.resize(minimumRoots);
        yValues.resize(minimumRoots);
    }

    double constantC=findConstantTerm(xValues,yValues);
    cout << "The value of c is : " << (long long)round(constantC) << endl;
    return 0;
}
