#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <tuple>

using namespace std;

int main() {
    vector<int> nums;
    string line;
    cin >> line;
    istringstream iss(line);
    string numFragment;
    int minimum = 1e9, maximum = -1;
    while(getline(iss, numFragment, ',')) {
        int num = atoi(numFragment.c_str());
        nums.push_back(num);
        minimum = min(num, minimum);
        maximum = max(num, maximum);
    }
    int best = -1, bestVal = 1e9;
    for(int i = minimum; i < maximum; ++i) {
        int cost = 0;
        for(int j = 0; j < nums.size(); ++j) {
            cost += abs(nums[j] - i);
        }
        if(cost < bestVal) {
            best = i;
            bestVal = cost;
        }
    }
    printf("target %d costs %d\n", best, bestVal);
}