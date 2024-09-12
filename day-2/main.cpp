#include <iostream>
#include <fstream>
#include <unordered_map> 
using namespace std;

const int RED_LIMIT = 12;
const int GREEN_LIMIT = 13;
const int BLUE_LIMIT = 14;

/*
// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
    // split based on : -> arr1
        // split arr1[1] based on ; -> arr2
            // split arr2[i] based on , -> arr3
*/

int getColorCount(vector<string> eachcolor, string color){         // [" 3 blue"," 4 red"]

    for(auto x : eachcolor){
        if(x.substr(x.length() - color.length()) == color){
            return stoi(x.substr(1, x.length() - color.length() - 1));
        }
    }

    return 0;
}

vector<string> split(string input, char sep){
    vector<string> res;
    string temp = "";
    for(auto x : input){
        if(x == sep){
            if(temp != "") res.push_back(temp);
            temp = "";
        }else{
            temp += x;
        }
    }
    if(temp != "") res.push_back(temp);
    return res;
}

int solveV1(string input){
    vector<string> game = split(input, ':');    
    int gameNumber = stoi(split(game[0], ' ')[1]);

    vector<string> attempt = split(game[1], ';');
    for(auto each : attempt){
        vector<string> eachcolor = split(each, ',');        // [" 3 blue"," 4 red"]
        int redCount = getColorCount(eachcolor, "red");
        int greenCount = getColorCount(eachcolor, "green");
        int blueCount = getColorCount(eachcolor, "blue");
        if(redCount > RED_LIMIT || greenCount > GREEN_LIMIT || blueCount > BLUE_LIMIT) return 0;
    }

    return gameNumber;
}

int solve(string input){
    vector<string> game = split(input, ':');    
    int gameNumber = stoi(split(game[0], ' ')[1]);

    vector<string> attempt = split(game[1], ';');
    int red = 0, green = 0, blue = 0;
    for(auto each : attempt){
        vector<string> eachcolor = split(each, ',');        // [" 3 blue"," 4 red"]
        int redCount = getColorCount(eachcolor, "red");
        int greenCount = getColorCount(eachcolor, "green");
        int blueCount = getColorCount(eachcolor, "blue");
        red = max(red, redCount); green = max(green, greenCount); blue = max(blue, blueCount);
    }

    return red * green * blue;
}

void setup(){
    return;
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
        res += solve(line);
        cout << line << " " << res << endl;   
    }

    cout << res << endl;   

    file.close();
    return 0;
}