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
    int illegalCount[4];
    int illegalWeight[] = {3, 57, 1197, 25137};
    memset(illegalCount, 0, sizeof(illegalCount));
    vector<int> stack;
    while(cin >> line) {
        stack.clear();
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
            ++illegalCount[type];
            break;
        }
    }
    int score = 0;
    for(int i = 0; i < 4; ++i) {
        score += illegalCount[i]*illegalWeight[i];
    }
    printf("%d\n", score);
}