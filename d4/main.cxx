#include <iostream>
#include <string>
#include <fstream>
#include <helpers.h>
#include <set>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

set<int> parse_numbers(string& str) {
    set<int> res;
    auto vec = split_string(str, ' ');
    for (auto item : vec) {
        if (item == "" || item == " ")
            continue;
        res.insert(stoi(item));
    }
    return res;
}

int compute_score(int count) {
    int score = 0;
    for (int i = 0; i < count; i++) {
        if (i == 0)
            score++;
        else {
            score *= 2;
        }
    }
    return score;
}

void task1() {
    ifstream file("../d4/input");
    string line;

    int sum = 0;
    while(getline(file, line)) {
        //cout << line << endl;
        line = line.substr(line.find(':')+2);

        // Split on | and divide into sets
        string winning = line.substr(0, line.find('|')-1);
        string hand = line.substr(line.find('|')+2);
        //cout << winning << endl;
        set<int> winning_set = parse_numbers(winning);
        set<int> hand_set = parse_numbers(hand);

        set<int> intersection;
        std::set_intersection(
            winning_set.begin(), winning_set.end(),
            hand_set.begin(), hand_set.end(),
            std::inserter(intersection, intersection.begin())
        );
        
        int score = compute_score(intersection.size());
        cout << "score: " << score << endl;
        sum += score;

    }

    cout << "Sum: " << sum << endl;
}

void task2() {
    int sum;
    // Each matching number between hand and winnig set wins a copy of the card to come
    ifstream file ("../d4/input");
    string line;

    // Parse lines int vector of mapping from copies to string
    vector<pair<int, string>> cards;
    while(getline(file, line)) {
        line = line.substr(line.find(':')+2);
        cards.push_back({1, line});
    }

    // Calculate matches
    for (int i = 0; i < cards.size(); i++) {
        int copies = cards[i].first;
        line = cards[i].second;
        // Split on | and divide into sets
        string winning = line.substr(0, line.find('|')-1);
        string hand = line.substr(line.find('|')+2);
        set<int> winning_set = parse_numbers(winning);
        set<int> hand_set = parse_numbers(hand);

        set<int> intersection;
        std::set_intersection(
            winning_set.begin(), winning_set.end(),
            hand_set.begin(), hand_set.end(),
            std::inserter(intersection, intersection.begin())
        );
        int matches = intersection.size();  

        sum += copies;

        // Increment the follwing card (count of matches) copies by one 
        for (int j = i+1; j < i+1+matches && j < cards.size(); j++) {
            cards[j].first += copies;
            //cout << "adding " << copies << " to card " << j << endl;
        }
    }

    // for (auto pair : cards) {
    //     cout << pair.first << endl;
    // }

    cout << "sum " << sum << endl;

}

int main() {
    task2();
}