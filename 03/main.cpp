#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string buffer;
    vector<int> count;
    while(cin >> buffer) {
        if(count.size() == 0) {
            count.resize(buffer.size());
        }
        for(int i = 0; i < buffer.size(); ++i) {
            count[i] += buffer[i] == '0' ? -1 : 1;
        }
    }
    int gamma = 0, epsilon = 0;
    for(int i = 0; i < count.size(); ++i) {
        int val = (count[count.size() - i - 1] > 0) ? 1 : 0;
        gamma |= val << i;
        epsilon |= (1-val) << i;
    }
    printf("%d * %d = %d\n", gamma, epsilon, gamma*epsilon);
}