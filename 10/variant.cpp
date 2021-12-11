#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <tuple>
#include <algorithm>

using namespace std;

int getType(char c) {
    switch(c) {
        case ')':
        case '(':
            return 0;
        case '[':
        case ']':
            return 1;
        case '{':
        case '}':
            return 2;
        default:
            return 3;
    }
}

bool isOpen(char c) {
    switch(c) {
        case '(':
        case '{':
        case '[':
        case '<':
            return true;
        default:
            return false;
    }
}

int main() {
    string line;
    vector<int> stack;
    vector<long long> scores;
    while(cin >> line) {
        stack.clear();
        bool wasIllegal = false;
        for(char c : line) {
            int type = getType(c);
            if(isOpen(c)) {
                stack.push_back(type);
                continue;
            }
            if(stack.size() != 0 && stack.back() == type) {
                stack.pop_back();
                continue;
            }
            wasIllegal = true;
            break;
        }
        if(wasIllegal) continue;
        long long score = 0;
        while(stack.size()) {
            int type = stack.back();
            stack.pop_back();
            score = score*5 + type + 1;
        }
        scores.push_back(score);
    }
    sort(scores.begin(), scores.end());
    printf("%lld\n", scores[scores.size()/2]);
}