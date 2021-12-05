#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int batoi(string const & val) {
    int sum = 0;
    for(int i = 0; i < val.size(); ++i) {
        int bit = val[val.size() - i - 1] - '0';
        sum |= bit << i;
    }
    return sum;
}

void reduce(vector<string> & vals, int dir, int index) {
    int count = 0;
    for(int i = 0; i < vals.size(); ++i){
        count += vals[i][index] == '0' ? -1 : 1;
    }
    char bit = dir == 1 ?
        count < 0 ? '0' : '1' :
        count < 0 ? '1' : '0';
    vector<string> ret;
    for(int i = 0; i < vals.size(); ++i) {
        if(vals[i][index] != bit) continue;
        ret.push_back(vals[i]);
    }
    vals = ret;
}

int main() {
    vector<string> vals;
    string buffer;
    vector<int> count;
    while(cin >> buffer) {
        vals.push_back(buffer);
    }
    vector<string> workVals = vals;
    for(int i = 0; workVals.size() > 1; ++i) {
        reduce(workVals, 1, i);
    }
    int ogr = batoi(workVals[0]);
    workVals = vals;
    for(int i = 0; workVals.size() > 1; ++i) {
        reduce(workVals, 0, i);
    }
    int co2sr = batoi(workVals[0]);
    printf("%d * %d = %d\n", ogr, co2sr, ogr * co2sr);
}