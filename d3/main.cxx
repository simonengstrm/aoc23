#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <regex>

using namespace std;

pair<int, int> get_first_of_num(int row, int col, vector<string>& lines) {
    int start = col;
    while(start > 0) {
        char current = lines.at(row).at(start-1);
        if(!isdigit((int)current)) {
            break;
        }
        start--;
    }

    return pair(row, start);
}

void neighbors(int row, int col, vector<string>& lines, set<pair<int,int>>& coords) {
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if ((i == 0 && j == 0) || (row+i < 0) || (col+j < 0) || (row+i >= lines.size()) || (col+j >= lines.at(row+i).size()))
                continue;
            if(isdigit((int)lines.at(row+i).at(col+j))) {
                auto res = coords.insert(get_first_of_num(row+i, col+j, lines));
            }
        }
    }
}

int parse_num(pair<int,int>& coord, vector<string>& lines) {
    int end = coord.second+1;
    while(end < lines.at(coord.first).size()) {
        char current = lines.at(coord.first).at(end);
        if(!isdigit((int)current)) {
            break;
        }
        end++;
    }

    string num = lines.at(coord.first).substr(coord.second, end-coord.second);
    string sOutput = std::regex_replace(num, std::regex(R"([\D])"), "");
    cout << "Coords: " << coord.first << "," << coord.second << ":" << end << "; Number: " << sOutput << endl;
    return stoi(sOutput);
}

int calc_gear(int row, int col, vector<string>& lines) {
    int ratio = 1;
    set<pair<int,int>> coords;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if ((i == 0 && j == 0) || (row+i < 0) || (col+j < 0) || (row+i >= lines.size()) || (col+j >= lines.at(row+i).size()))
                continue;
            if(isdigit((int)lines.at(row+i).at(col+j))) {
                auto res = coords.insert(get_first_of_num(row+i, col+j, lines));
            }
        }
    }

    if (coords.size() == 2) {
        for (auto coord : coords) {
            ratio *= parse_num(coord, lines);
        }
    } else {
        return 0;
    }

    return ratio;
}

void task2() {
    ifstream file("../d3/input.txt");
    string line;
    vector<string> lines;

    while(getline(file, line)) {
        lines.push_back(line);
    }

    int sum = 0;

    set<pair<int,int>> coordinates;
    for (int row = 0; row < lines.size(); row++) {
        string current = lines.at(row);
        for (int col = 0; col < current.size(); col++) {
            if (current.at(col) == '*') {
                sum += calc_gear(row, col, lines);
            }
        }
    } 


    cout << "Sum: " << sum << endl;
}

void task1() {
    ifstream file("../d3/input.txt");
    string line;
    vector<string> lines;

    while(getline(file, line)) {
        lines.push_back(line);
    }

    set<pair<int,int>> coordinates;
    for (int row = 0; row < lines.size(); row++) {
        string current = lines.at(row);
        for (int col = 0; col < current.size(); col++) {
            if (!isdigit((int)current.at(col)) && current.at(col) != '.') {
                //cout << "Symbol found at " << row << "," << col << endl;
                neighbors(row, col, lines, coordinates);
            }
        }
    } 

    int sum = 0;

    for (auto coord : coordinates) 
        sum += parse_num(coord, lines);

    cout << "Sum: " << sum << endl;
}

int main() {
    task2();
}