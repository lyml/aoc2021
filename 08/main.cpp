#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <tuple>

using namespace std;

int main() {
    string line;
    int count = 0;
    while(getline(cin, line)) {
        istringstream iss(line);
        string fragment;
        while(iss >> fragment) {
            if(fragment == "|") {
                break;
            }
        }
        int subCount = 0;
        for(int i = 0; i < 4; ++i) {
            iss >> fragment;
            int length = fragment.length();
            switch(fragment.length()) {
                case 2:
                case 3:
                case 4:
                case 7:
                    ++subCount;
                default:
                break;
            }
        }
        printf("line has %d uniques\n", subCount);
        count += subCount;
    }
    
    printf("%d easies\n", count);
}