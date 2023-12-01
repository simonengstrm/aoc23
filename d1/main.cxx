#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <map>

using namespace std;

void part1();
void part2();
void s_replace(string& str, string const& toreplace, string const& replacewith) {
    auto pos = str.find(toreplace);
    if (pos == string::npos)
        return;
    str.replace(pos, toreplace.length(), replacewith);
}

int main()
{
    part2();
}

void part2()
{
    // Read example file
    ifstream file("../d1/input");
    string line;

    vector<string> lines;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    map<string, int> digits = {
        {"zero", 0},
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}};

    int sum = 0;

    for (int i = 0; i < lines.size(); i++)
    {
        // Find first and last number for each line
        string current = lines.at(i);
        vector<tuple<int, int>> vec;

        // Find where each number is and save its index

        // 1. digits
        for (int j = 0; j < current.length(); j++) {
            if (isdigit((int)current[j])) {
                vec.push_back(tuple<int, int>(current[j]-'0', j));
            }
        }

        // 2. strings
        for (auto const &pair : digits) {
            size_t pos = current.find(pair.first, 0);
            while (pos != string::npos) {
                vec.push_back(tuple<int, int>(pair.second, pos));
                pos = current.find(pair.first, pos+1);
            }
        }

        // Find number with lowest and highest index
        int low = 1000;
        int high = 0;
        int first;
        int last;

        for(int j = 0; j < vec.size(); j++) {
            tuple<int, int> curr = vec.at(j);
            if (get<1>(curr) < low) {
                low = get<1>(curr);
                first = get<0>(curr);
            }
            if (get<1>(curr) >= high) {
                high = get<1>(curr);
                last = get<0>(curr);
            }
        }

        sum += stoi(to_string(first) + to_string(last));
    }

    cout << sum << endl;
}


void part1()
{
    // Read example file
    ifstream file("../d1/input");
    string line;

    vector<string> lines;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    int sum = 0;

    for (int i = 0; i < lines.size(); i++)
    {
        // Find first and last number for each line
        string current = lines.at(i);
        char first, last;

        // First
        for (int j = 0; j < current.length(); j++)
        {
            if (isdigit((int)current[j]))
            {
                first = current[j];
                break;
            }
        }

        for (int j = current.length() - 1; j >= 0; j--)
        {
            if (isdigit((int)current[j]))
            {
                last = current[j];
                break;
            }
        }

        sum += stoi(string(1, first) + last);
    }

    cout << sum << endl;
}