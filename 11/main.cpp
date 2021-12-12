#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <tuple>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

int board[12][12];
int dx[] = {  1,  1,  0, -1, -1, -1,  0,  1 };
int dy[] = {  0,  1,  1,  1,  0, -1, -1, -1 };

int main() {
    for(int i = 0; i < 12; ++i) {
        for(int j = 0; j < 12; ++j) {
            board[i][j] = INT_MIN;
        }
    }
    string line;
    for(int i = 0; cin >> line; ++i) {
        for(int j = 0; j < line.size(); ++j) {
            board[i+1][j+1] = line[j] - '0';
        }
    }

    int flashes = 0;
    vector<tuple<int,int>> stack;
    for(int i = 0; i < 100; ++i) {
        // increment all
        for(int i = 1; i < 11; ++i) {
            for(int j = 1; j < 11; ++j) {
                int & val = board[i][j];
                if(val++ == 9) {
                    stack.push_back(make_tuple(i,j));
                }
            }
        }
        // increment surrounding
        while(!stack.empty()) {
            auto [i,j] = stack.back();
            stack.pop_back();
            ++flashes;
            board[i][j] = INT_MIN;
            for(int k = 0; k < 8; ++k) {
                int & val = board[i+dy[k]][j+dx[k]];
                if(val++ == 9) {
                    stack.push_back(make_tuple(i+dy[k], j+dx[k]));
                }
            }
        }

        for(int i = 0; i < 10; ++i) {
            for(int j = 0; j < 10; ++j) {
                int & val = board[i+1][j+1];
                if(val < 0) {
                    val = 0;
                }
            }
        }
    }
    printf("%d\n", flashes);
}