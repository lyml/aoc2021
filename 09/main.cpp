#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <tuple>

using namespace std;

int b[102][102];

int main() {
    for(int i = 0; i < 102; ++i) {
        for(int j = 0; j < 102; ++j) {
            b[i][j] = 9;
        }
    }
    string line;
    int row = 1;
    while(cin >> line) {
        for(int i = 0; i < line.length(); ++i) {
            b[row][i+1] = line[i] - '0';
        }
        ++row;
    }

    int riskScore = 0;
    for(int i = 1; i < 101; ++i) {
        for(int j = 1; j < 101; ++j) {
            int x = b[i][j];
            if(x < b[i+1][j] && x < b[i][j+1] && x < b[i-1][j] && x < b[i][j-1]) {
                riskScore += x + 1;
            }
        }
    }
    printf("%d\n", riskScore);
}