#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <tuple>
#include <algorithm>
#include <cmath>

using namespace std;

int indices[10];
int index2num[10];

void setNum(int num, int index) {
    indices[num] = index;
    index2num[index] = num;
}

int overlap(string const & left, string const & right) {
    int count = 0;
    for(int i = 0; i < left.length(); ++i) {
        if(right.find(left[i]) != -1) ++count;
    }
    return count;
}

int solveSixSegments(string const & fragment, string const & one, string const & four) {
    int oneOverlap = overlap(fragment, one);
    int fourOverlap = overlap(fragment, four);
    return fourOverlap == 4 ? 9 : oneOverlap == 2 ? 0 : 6;
}

int solveFiveSegments(string const & fragment, string const & one, string const & four) {
    int fourOverlap = overlap(fragment, four);
    int oneOverlap = overlap(fragment, one);
    return fourOverlap == 2 ? 2 : oneOverlap == 2 ? 3 : 5;
}

int main() {
    string line;
    int sum = 0;
    while(getline(cin, line)) {
        istringstream iss(line);
        vector<string> fragments;
        string fragment;
        while(iss >> fragment) {
            if(fragment == "|") break;
            sort(fragment.begin(), fragment.end());
            int i = fragment.length();
            int k = i == 2 ? 1 : i == 3 ? 7 : i == 4 ? 4 : i == 7 ? 8 : -1;
            if(k > 0) setNum(k, fragments.size());
            fragments.push_back(fragment);
        }
        string const & one = fragments[indices[1]];
        string const & four = fragments[indices[4]];
        for(int i = 0; i < 10; ++i) {
            string const & fragment = fragments[i];
            if(fragment.length() == 5) setNum(solveFiveSegments(fragment, one, four), i);
            if(fragment.length() == 6) setNum(solveSixSegments(fragment, one, four), i);
        }
        for(int i = 0; i < 4; ++i) {
            iss >> fragment;
            sort(fragment.begin(), fragment.end());
            int index = find(fragments.begin(), fragments.end(), fragment) - fragments.begin();
            sum += pow(10, 3-i)*index2num[index];
        }
    }
    printf("%d\n", sum);
}