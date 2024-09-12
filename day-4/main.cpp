#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <map>
using namespace std;

class Utils{
    public:
    static bool isdigit(char ch){
        return ch >= '0' and ch <= '9';
    }
};

class InputReader{
    vector<string> allinputs;
    public:
    vector<string> getReadInputs(string inputFile){
        ifstream file(inputFile);
        if (!file.is_open()){
            cerr << "Error opening the file!" << endl;
            return allinputs;
        }

        string line;
        while (getline(file, line)) allinputs.push_back(line);
        file.close();
        return allinputs;
    }
};

/*
Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
*/

class Challenge{
    vector<string> giveninputs;
    public:
    Challenge(vector<string> inputs){
        giveninputs = inputs;
    }

    void setup(){
        
    }

    long long solve(){
        long long res = 0;
        for(auto eachinput : giveninputs){
            res += solveEach(eachinput);
        }
        return res;
    }

    long long solveEach(string input){

        unordered_set<int> winners;
        int i = 0, n = input.length();
        while(i < n and input[i] != ':') i++;

        i++;    // skip :
        string temp = "";
        while(i < n and input[i] != '|'){
            if(Utils::isdigit(input[i])){
                temp += input[i];
            }else{
                if(temp != "") winners.insert(stoi(temp));
                temp = "";
            }
            i++;
        }
        if(temp != "") winners.insert(stoi(temp));
        temp = "";

        i++;    // skip |
        long long res = 0;
        while(i < n){
            if(Utils::isdigit(input[i])){
                temp += input[i];
            }else{
                if(temp != "" and winners.find(stoi(temp)) != winners.end()){ 
                    if(res == 0) res = 1;
                    else res = res * 2;
                }
                temp = "";
            }
            i++;
        }

        if(temp != "" and winners.find(stoi(temp)) != winners.end()){ 
            if(res == 0) res = 1;
            else res = res * 2;
        }

        return res;
    }

};

int main(int argc, char *args[]){

    InputReader *inputReader = new InputReader();
    Challenge *challenge = new Challenge(inputReader->getReadInputs(args[1]));

    long long res = challenge->solve();
    cout << res << endl;

    return 0;
}