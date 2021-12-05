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

int signum(int x) {
    if(x < 0) return -1;
    return x > 0 ? 1 : 0;
}

int board[1000][1000];
int main() {
    memset(board, 0, sizeof(board));
    string sp1, sp2, junk;
    while(cin >> sp1 >> junk >> sp2) {
        auto a = parsePoint(sp1);
        auto b = parsePoint(sp2);
        int dx = signum(b.x - a.x);
        int dy = signum(b.y - a.y);
        int count = max(abs(a.x - b.x), abs(a.y - b.y)) + 1;
        for(int i = 0; i < count; ++i) {
            ++board[a.x + i*dx][a.y + i*dy];
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