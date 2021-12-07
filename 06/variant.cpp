#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <tuple>

using namespace std;

typedef long long ll;

int main() {
    ll vals[9];
    memset(vals, 0, sizeof(vals));
    string line;
    cin >> line;
    istringstream iss(line);
    string numFragment;
    while(getline(iss, numFragment, ',')) {
        int num = atoi(numFragment.c_str());
        ++vals[num];
    }

    for(int i = 0; i < 256; ++i) {
        ll carry = vals[0];
        for(ll j = 1; j < 9; ++j) {
            vals[j-1] = vals[j];
        }
        vals[8] = carry;
        vals[6] += carry;
    }
    ll count = 0;
    for(int i = 0; i < 9; ++i) {
        count += vals[i];
    }
    cout << count << endl;
}