#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

std::string trimStart(const std::string& s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        ++start;
    }
    return std::string(start, s.end());
}

// Function to trim whitespace from the end of a string
std::string trimEnd(const std::string& s) {
    auto end = s.end();
    while (end != s.begin() && std::isspace(*(end - 1))) {
        --end;
    }
    return std::string(s.begin(), end);
}

// Function to trim whitespace from both the start and end of a string
std::string trim(const std::string& s) {
    return trimEnd(trimStart(s));
}

vector<string> split_string(string& str, char token) {
    vector<string> res;
    auto pos = str.find(token);
    while(pos != string::npos) {
        auto substr = str.substr(0, pos);
        res.push_back(trim(substr));
        str = str.erase(0, pos+1);
        pos = str.find(token);
    }
    res.push_back(trim(str));
    return res;
}

map<string, int> parse_set(string& set) {
    map<string, int> res;
    auto cubes = split_string(set, ',');
    for (string& cube : cubes) {
        auto split = split_string(cube, ' ');
        res.insert({split.at(1), stoi(split.at(0))});
    }
    return res;
}

vector<map<string, int>> parse_sets(string& line) {
    vector<map<string,int>> res;
    auto sets = split_string(line, ';');
    for (string& str : sets) {
        map<string, int> set = parse_set(str);
        res.push_back(set);
    }

    return res;
}

int main()
{
    ifstream file("../d2/input");
    string line;
    vector<string> lines;

    int red_limit = 12;
    int blue_limit = 14;
    int green_limit = 13;

    int gameid = 1;
    int sum = 0;
    int power_sum = 0;

    while(getline(file, line))
    {
        string parsed_line = line.erase(0, line.find(':')+2);
        vector<map<string, int>> sets = parse_sets(parsed_line);
        bool valid = true;
        int min_red = 0;
        int min_blue = 0;
        int min_green = 0;
        for (map<string, int> set : sets) {
            for (auto pair : set) {
                if (pair.first == "red") {
                    if (pair.second > red_limit)
                        valid = false;
                    
                    if (pair.second > min_red)
                        min_red = pair.second;
                }
                if (pair.first == "green") {
                    if (pair.second > green_limit)
                        valid = false;

                    if (pair.second > min_green)
                        min_green = pair.second;
                }
                if (pair.first == "blue") {
                    if (pair.second > blue_limit) 
                        valid = false;
                    
                    if (pair.second > min_blue)
                        min_blue = pair.second;
                }


            }
        }
        if (valid) {
            sum += gameid;
        }
        min_blue = max(min_blue, 1);
        min_green = max(min_green, 1);
        min_red = max(min_red, 1);

        power_sum += min_blue * min_green * min_red;

        gameid++;
    }

    cout << "Sum: " << sum << endl;
    cout << "Power: " << power_sum << endl;

}