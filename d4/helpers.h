#include <string>
#include <vector>

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