#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <tuple>

using namespace std;

struct Point {
    int x, y;
};

Point parsePoint(string const & sp) {
    istringstream iss(sp);
    Point p;
    string sx;
    getline(iss, sx, ',');
    iss >> p.y;
    p.x = atoi(sx.c_str());
    return p;
}

int main() {
    int board[1000][1000];
    memset(board, 0, sizeof(board));
    string sp1, sp2, junk;
    while(cin >> sp1 >> junk >> sp2) {
        auto p1 = parsePoint(sp1);
        auto p2 = parsePoint(sp2);
        if(p1.x == p2.x) {
            int from = min(p1.y, p2.y);
            int to = max(p1.y, p2.y);
            for(int i = from; i <= to; ++i) {
                ++board[p1.x][i];
            }
        }
        else if(p1.y == p2.y) {
            int from = min(p1.x, p2.x);
            int to = max(p1.x, p2.x);
            for(int i = from; i <= to; ++i) {
                ++board[i][p1.y];
            }
        }
    }
    int overlaps = 0;
    for(int i = 0; i < 1000; ++i){
        for(int j = 0; j < 1000; ++j) {
            if(board[i][j] > 1) ++overlaps;
        }
    }
    cout << overlaps << endl;
}