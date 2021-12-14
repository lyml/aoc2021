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

typedef long long ll;

int const undefined = -1;

int const A = 'Z' - 'A' +1;
int const P = 100;
int const S = 41;
ll mem[A][P][S];

void clearMem() {
    for(int i = 0; i < A; ++i) {
        for(int j = 0; j < P; ++j) {
            for(int k = 0; k < S; ++k) {
                mem[i][j][k] = undefined;
            }
        }
    }
}

vector<tuple<string, char>> insertions;

int findPair(char a, char b) {
    for(int i = 0; i < insertions.size(); ++i) {
        auto [pair, c] = insertions[i];
        if(pair[0] == a && pair[1] == b) return i;
    }
    return -1;
}

ll solve(int c, int pair, int step);
ll dp(int c, int pair, int step) {
    ll & val = mem[c][pair][step];
    if(val == undefined) val = solve(c, pair, step);
    return val;
}

ll solve(int c, int pair, int step) {
    if(step == 0) return 0;
    auto [polymer, insertion] = insertions[pair];
    int insert1 = findPair(polymer[0], insertion);
    int insert2 = findPair(insertion, polymer[1]);
    ll sum = insertion == c + 'A' ? 1 : 0;
    sum += insert1 == undefined ? 0 : dp(c, insert1, step-1);
    sum += insert2 == undefined ? 0 : dp(c, insert2, step-1);
    return sum;
}

int main() {
    string polymer;
    cin >> polymer;
    {
        string junk, pair;
        char c;
        while(cin >> pair >> junk >> c) {
            insertions.push_back(make_tuple(pair, c));
        }
    }

    clearMem();

    vector<ll> counts;
    counts.resize(A);
    for(int i = 0; i < polymer.length(); ++i) {
        ++counts[polymer[i]-'A'];
    }
    for(int i = 1; i < polymer.length(); ++i) {
        int insertionPair = findPair(polymer[i-1], polymer[i]);
        if(insertionPair == undefined) continue;
        for(int j = 0; j < A; ++j) {
            counts[j] += dp(j, insertionPair, 40);
        }
    }
    ll mostCommon = 0;
    ll leastCommon = 1e18;
    for(ll count : counts) {
        if(!count) continue;
        mostCommon = max(mostCommon, count);
        leastCommon = min(leastCommon, count);
    }
    printf("%lld - %lld = %lld\n", mostCommon, leastCommon, mostCommon - leastCommon);
}