#include <iostream>
#include <climits>

using namespace std;

int main() {
    int val, prev = INT_MAX;
    int count = 0;
    while(cin >> val) {
        if(val > prev) ++count;
        prev = val;
    }
    cout << count << endl;
}