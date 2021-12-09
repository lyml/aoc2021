#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <tuple>
#include <algorithm>

using namespace std;

int board[102][102];

int main() {
    for(int i = 0; i < 102; ++i) {
        for(int j = 0; j < 102; ++j) {
            board[i][j] = 9;
        }
    }
    string line;
    for(int i = 1; cin >> line; ++i) {
        for(int j = 0; j < line.length(); ++j) {
            board[i][j+1] = line[j] - '0';
        }
    }
    int dx[] = { 1, -1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };
    vector<int> basin;
    for(int r = 0; r < 9; ++r) {
        for(int i = 1; i < 101; ++i) {
            for(int j = 1; j < 101; ++j) {
                int & current = board[i][j];
                if(current != r) continue;
                bool isPartOfBasin = false;
                for(int k = 0; k < 4; ++k) {
                    int neighbour = board[i+dy[k]][j+dx[k]];
                    if(neighbour < 10) continue;
                    current = neighbour;
                    isPartOfBasin = true;
                }
                if(isPartOfBasin) continue;
                current = basin.size() + 10;
                basin.push_back(0);
            }
        }
    }
    for(int i = 1; i < 101; ++i) {
        for(int j = 1; j < 101; ++j) {
            if(board[i][j] < 10) continue;
            ++basin[board[i][j]-10];
        }
    }
    sort(basin.begin(), basin.end(), std::greater<int>());
    printf("score: %d\n", basin[0]*basin[1]*basin[2]);
}
