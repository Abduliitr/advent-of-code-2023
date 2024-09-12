#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
using namespace std;

/*
467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..
*/

bool isdigit(char ch)
{
    return (ch >= '0' and ch <= '9');
}

bool isvalid(int x, int y, int n, int m)
{
    return x >= 0 and x < n and y >= 0 and y < m;
}

bool exploreV2(vector<string> &matrix, int idx, int start, int end, map<pair<int, int>, vector<int> > &numberAdj){
    int n = matrix.size(), m = matrix[0].size();
    int num = stoll(matrix[idx].substr(start, end - start + 1));
    // explore prev row
    for (int j = start - 1; j <= end + 1; j++)
    {
        if (isvalid(idx - 1, j, n, m) and matrix[idx - 1][j] == '*') numberAdj[make_pair(idx - 1, j)].push_back(num);
    }

    // explore next row
    for (int j = start - 1; j <= end + 1; j++)
    {
        if (isvalid(idx + 1, j, n, m) and matrix[idx + 1][j] == '*') numberAdj[make_pair(idx + 1, j)].push_back(num);
    }

    // explore same row
    if (isvalid(idx, start - 1, n, m) and matrix[idx][start - 1] == '*') numberAdj[make_pair(idx, start - 1)].push_back(num);
    if (isvalid(idx, end + 1, n, m) and matrix[idx][end + 1] == '*') numberAdj[make_pair(idx, end + 1)].push_back(num);

    return false;
}


bool explore(vector<string> matrix, int idx, int start, int end)
{
    int n = matrix.size(), m = matrix[0].size();

    // explore prev row
    for (int j = start - 1; j <= end + 1; j++)
    {
        if (isvalid(idx - 1, j, n, m) and
            (!isdigit(matrix[idx - 1][j]) and matrix[idx - 1][j] != '.')
            // may need to check is not alphabet
        ) return true;
    }

    // explore next row
    for (int j = start - 1; j <= end + 1; j++)
    {
        if (isvalid(idx + 1, j, n, m) and
            (!isdigit(matrix[idx + 1][j]) and matrix[idx + 1][j] != '.')
            // may need to check is not alphabet
        ) return true;
    }

    // explore same row
    if (isvalid(idx, start - 1, n, m) and
            (!isdigit(matrix[idx][start - 1]) and matrix[idx][start - 1] != '.')
            // may need to check is not alphabet
    ) return true;

    if (isvalid(idx, end + 1, n, m) and
        (!isdigit(matrix[idx][end + 1]) and matrix[idx][end + 1] != '.')
        // may need to check is not alphabet
    ) return true;

    return false;
}

long long solve(vector<string> input)
{
    int n = input.size(), m = input[0].size();
    long long res = 0;

    for (int i = 0; i < n; i++)
    {
        int start = -1, end = -1;
        for (int j = 0; j < m; j++)
        {
            if (isdigit(input[i][j]))
            {
                if (start == -1) start = j;
                end = j;
            }
            else
            {
                if (start != -1)
                {
                    // we found some number
                    // explore all the neighbours to determine if its eligible or not.
                    if (explore(input, i, start, end))
                    {
                        res += stoll(input[i].substr(start, end - start + 1));
                        // cout << i << " " << start << " " << end << " " << input[i].substr(start, end - start + 1) << endl;
                    }
                }
                start = -1;
                end = -1;
            }
        }

        if (start != -1)
        {
            // we found some number
            // explore all the neighbours to determine if its eligible or not.
            if (explore(input, i, start, end))
            {
                res += stoll(input[i].substr(start, end - start + 1));
                // cout << i << " " << input[i].substr(start, end - start + 1) << endl;
            }
        }
    }

    return res;
}

long long solveV2(vector<string> &input){
    map<pair<int, int>, vector<int> > numberAdj;
    int n = input.size(), m = input[0].size();
    long long res = 0;

    for (int i = 0; i < n; i++){
        int start = -1, end = -1;
        for (int j = 0; j < m; j++){
            if (isdigit(input[i][j])){
                if (start == -1) start = j;
                end = j;
            }
            else
            {
                if (start != -1) {
                    exploreV2(input, i, start, end, numberAdj);
                }
                start = -1;
                end = -1;
            }
        }

        if (start != -1) exploreV2(input, i, start, end, numberAdj);
    }

    for(auto mp : numberAdj){
        if(mp.second.size() == 2){
            res += 1ll*mp.second[0] * mp.second[1];
        }
    }

    return res;
}

void setup()
{
    return;
}

int main(int argc, char *args[])
{
    string inputfile = args[1];
    ifstream file(inputfile);

    if (!file.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return -1;
    }

    setup();

    string line;
    long long res = 0;
    vector<string> giveninput;
    while (getline(file, line))
    {
        // res += solve(line);
        giveninput.push_back(line);
        // cout << line << " " << res << endl;
    }

    res = solveV2(giveninput);
    cout << res << endl;

    file.close();
    return 0;
}