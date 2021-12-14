#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <tuple>
#include <algorithm>
#include <climits>
#include <queue>
#include <map>
#include <set>

using namespace std;

int main() {
    string polymer;
    vector<tuple<string, char>> insertions;
    cin >> polymer;
    {
        string junk, pair;
        char c;
        while(cin >> pair >> junk >> c) {
        insertions.push_back(make_tuple(pair, c));
        }
    }
    for(int k = 0; k < 10; ++k) {
        string polymer2;
        polymer2.push_back(polymer[0]);
        for(int i = 1; i < polymer.length(); ++i) {
            for(auto [pair, c] : insertions) {
                if(polymer[i-1] == pair[0] && polymer[i] == pair[1]) {
                    polymer2.push_back(c);
                }
            }
            polymer2.push_back(polymer[i]);
        }
        swap(polymer, polymer2);
        polymer2.clear();
    }
    vector<int> counts;
    counts.resize(27);
    for(int i = 0; i < polymer.length(); ++i) {
        ++counts[polymer[i]-'A'];
    }
    int mostCommon = 0;
    int leastCommon = 1e9;
    for(int count : counts) {
        if(!count) continue;
        mostCommon = max(mostCommon, count);
        leastCommon = min(leastCommon, count);
    }
    printf("%d - %d = %d\n", mostCommon, leastCommon, mostCommon - leastCommon);
}