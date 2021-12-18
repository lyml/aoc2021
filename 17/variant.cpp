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
#include <unistd.h>

using namespace std;

int main() {
    string junk, xString, yString;
    cin >> junk >> junk >> xString >> yString;
    xString = xString.substr(2, xString.length()-3);
    yString = yString.substr(2);
    auto [x1, x2] = split(xString);
    auto [y1, y2] = split(yString);
    int solves = 0;
    for(int i = 0; i < 1000; ++i) {
        for(int j = -1000; j < 1000; ++j) {
            int x = 0, y = 0, dx = i, dy = j;
            int maxY = 0;
            while(x <= x2 && y >= y1) {
                x += dx;
                dx = max(dx-1, 0);
                y += dy;
                dy = dy - 1;
                if(y <= y2 && y >= y1 && x >= x1 && x <= x2) {
                    ++solves;
                    break;
                }
            }
        }
    }
    printf("%d\n", solves);
}