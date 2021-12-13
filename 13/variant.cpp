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

int fold(int num, int point) {
    if(num < point) return num;
    return point - (num-point);
}

int main() {
    vector<tuple<int,int>> points;
    string line;
    while(getline(cin, line)) {
        if(line == "") break;
        istringstream iss(line);
        string xString;
        getline(iss, xString, ',');
        int x = atoi(xString.c_str()), y;
        iss >> y;
        points.push_back(make_tuple(x,y));
    }
    string junk;
    
    while(cin >> junk >> junk >> line) {
        istringstream iss(line);
        string axis;
        int foldPoint;
        getline(iss, axis, '=');
        iss >> foldPoint;
        set<tuple<int,int>> foldedPoints;
        for(int i = 0; i < points.size(); ++i) {
            auto & [x,y] = points[i];
            x = axis == "x" ? fold(x, foldPoint) : x;
            y = axis == "y" ? fold(y, foldPoint) : y;
        }
    }
    int maxX = -1e9, maxY = -1e9;
    for(int i = 0; i < points.size(); ++i) {
        auto [x, y] = points[i];
        maxX = max(x, maxX);
        maxY = max(y, maxY);
    }
    vector<string> lines;
    for(int i = 0; i <= maxY; ++i) {
        lines.push_back(string(maxX+1, '.'));
    }
    for(int i = 0; i < points.size(); ++i) {
        auto [x, y] = points[i];
        lines[y][x] = '#';
    }
    for(int i = 0; i < lines.size(); ++i) {
        printf("%s\n", lines[i].c_str());
    }
}