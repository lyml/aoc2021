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

int board[102][102];
bool visited[102][102];

int main() {
    for(int i = 0; i < 102; ++i) {
        for(int j = 0; j < 102; ++j) {
            board[i][j] = -1;
            visited[i][j] = false;
        }
    }
    string line;
    for(int i = 0; getline(cin, line); ++i) {
        for(int j = 0; j < line.size(); ++j) {
            board[i+1][j+1] = line[j]-'0';
        }
    }
    int destX = line.size();
    int destY = line.size();
    printf("going to %d %d\n", destX, destY);
    auto comp = [](tuple<int,int,int> lhs, tuple<int,int,int> rhs) -> bool { return get<2>(lhs) > get<2>(rhs); };
    auto cont = vector<tuple<int,int,int>>();
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, decltype(comp)> q(comp);
    q.push(make_tuple(1,1,0));
    int dx[] = { 1, 0, -1, 0};
    int dy[] = { 0, -1, 0, 1};
    while(!q.empty()) {
        auto [x, y, score] = q.top();
        q.pop();
        if(visited[y][x]) continue;
        if(board[y][x] == -1) continue;
        visited[y][x] = true;
        if(x == destX && y == destY) {
            printf("%d\n", score);
            return 0;
        }
        for(int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nextScore = score+board[nx][ny];
            q.push(make_tuple(nx, ny, nextScore));
        }
    }

    printf("no solution found\n");
}