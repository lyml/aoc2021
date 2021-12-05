#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <tuple>

using namespace std;

struct Board {
    Board() = default;
    Board(unsigned int * in) {
        for(int i = 0; i < 25; ++i) vals[i] = in[i];
    }
    unsigned int vals[25];
    unsigned int & operator[](std::size_t i) {
        return vals[i];
    }

};

tuple<vector<Board>, vector<int>> readInput() {
    vector<Board> boards;
    string numsString;
    getline(cin, numsString);
    istringstream iss(numsString);
    vector<int> nums;
    string numString;
    while(getline(iss, numString, ',')) {
        nums.push_back(atoi(numString.c_str()));
    }
    unsigned int board[25];
    while(cin >> board[0]) {
        for(int i = 1; i < 25; ++i) {
            cin >> board[i];
        }
        boards.push_back(board);
    }
    return make_tuple(boards, nums);
}

bool isSolved(Board & board) {
    bool solved[10];
    memset(solved, 1, sizeof(solved));
    for(int j = 0; j < 5; ++j) {
        for(int k = 0; k < 5; ++k) {
            if((int)board[5*j + k] > 0) solved[k] = false;
            if((int)board[5*k + j] > 0) solved[5+k] = false;
        }
    }
    for(int i = 0; i < 10; ++i) {
        if(solved[i]) return true;
    }
    return false;
}

int getBoardScore(Board & board) {
    int score = 0;
    for(int i = 0; i < 25; ++i) {
        int val = board[i];
        if(val < 0) continue;
        score += val;
    }
    return score;
}

void printBoard(Board board) {
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
            int val = board[i*5 + j];
            if(val < 0) printf(" **");
            else {
                printf(" %2d", val);
            }
        }
        printf("\n");
    }
}

int main() {
    auto [boards, nums] = readInput();
    for(int num : nums) {
        for(auto & board : boards) {
            for(int j = 0; j < 25; ++j) {
                auto & col = board[j];
                if(col == num) {
                    col ^= (unsigned int)-1;
                }
            }
            if(isSolved(board)) {
                int boardScore = getBoardScore(board);
                printf("%d * %d = %d\n", boardScore, num, boardScore * num);
                return 0;
            }
        }
    }
}