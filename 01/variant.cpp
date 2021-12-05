#include <iostream>
#include <climits>

using namespace std;

int main() {
    int buffer[4];
    int i = 0;
    int count = 0;
    while(cin >> buffer[(i++)%4]) {
        if(i < 4) continue;
        int lhs = 0, rhs = 0;
        for(int j = 0; j < 3; ++j) {
            lhs += buffer[(j+i-4)%4];
            rhs += buffer[(j+i-3)%4];
        }
        printf("%d: %d %d\n", i, lhs, rhs);
        if(lhs < rhs) {
            ++count;
        }
    }
    cout << count << endl;
}