#include <iostream>
#include <fstream>
#include <unordered_map> 
using namespace std;

unordered_map<string, int> numberMapping;

string getLast(string st, int idx, int k){
    // 0, 1, 2
    if(idx - k + 1 < 0) return "";  // last k doesnt exist.
    return st.substr(idx - k + 1, k);
}

string getNext(string st, int idx, int k){
    // st.len = 5, idx = 2, k = 3
    if(idx + k - 1 > st.length() - 1) return "";        // next k doesnt exist
    return st.substr(idx, k);
}

int getCalibrationV1(string line){
    int first = 0, second = 0;
    for(int i = 0; i < line.length(); i++){
        if(line[i] >= '0' and line[i] <= '9'){
            first = line[i] - '0';
            break;
        }

        if(numberMapping.find(getLast(line, i, 3)) != numberMapping.end()){
            first = numberMapping[getLast(line, i, 3)];
            break;
        }

        if(numberMapping.find(getLast(line, i, 4)) != numberMapping.end()){
            first = numberMapping[getLast(line, i, 4)];
            break;
        }

        if(numberMapping.find(getLast(line, i, 5)) != numberMapping.end()){
            first = numberMapping[getLast(line, i, 5)];
            break;
        }
    }

    for(int i = line.length()-1; i >= 0; i--){
        if(line[i] >= '0' and line[i] <= '9'){
            second = line[i] - '0';
            break;
        }

        if(numberMapping.find(getNext(line, i, 3)) != numberMapping.end()){
            second = numberMapping[getNext(line, i, 3)];
            break;
        }

        if(numberMapping.find(getNext(line, i, 4)) != numberMapping.end()){
            second = numberMapping[getNext(line, i, 4)];
            break;
        }

        if(numberMapping.find(getNext(line, i, 5)) != numberMapping.end()){
            second = numberMapping[getNext(line, i, 5)];
            break;
        }
    }

    return first * 10 + second;
}

/*
one, two, three, four, five, six, seven, eight, and nine
*/

int getCalibrationV2(string line){
    int first = 0, second = 0;
    for(int i = 0; i < line.length(); i++){
        if(line[i] >= '0' and line[i] <= '9'){
            first = line[i] - '0';
            break;
        }
    }

    for(int i = line.length()-1; i >= 0; i--){
        if(line[i] >= '0' and line[i] <= '9'){
            second = line[i] - '0';
            break;
        }
    }

    return first * 10 + second;
}

void setup(){
    numberMapping["one"]    = 1;
    numberMapping["two"]    = 2;
    numberMapping["three"]  = 3;
    numberMapping["four"]   = 4;
    numberMapping["five"]   = 5;
    numberMapping["six"]    = 6;
    numberMapping["seven"]  = 7;
    numberMapping["eight"]  = 8;
    numberMapping["nine"]   = 9;
}

int main(int argc, char* args[]){
    string inputfile = args[1];

    ifstream file(inputfile);

    if(!file.is_open()){
        cerr << "Error opening the file!" << endl;
        return -1;
    }

    setup();

    string line;
    int res = 0;
    while(getline(file, line)){
        res += getCalibrationV1(line);
        // cout << line << " " << res << endl;   
    }

    cout << res << endl;   

    file.close();
    return 0;
}