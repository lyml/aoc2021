#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <tuple>
#include <algorithm>
#include <climits>
#include <queue>
#include <map>

using namespace std;

struct Node {
    vector<int> edges;
    int visits;
};

vector<Node> nodes;
map<string, int> labels;

int solve(int curr, int dest) {
    if(curr == dest) return 1;
    auto & node = nodes[curr];
    if(node.visits > 0) return 0;
    node.visits += 1;
    int ret = 0;
    for(int next : node.edges) {
        ret += solve(next, dest);
    }
    node.visits -= 1;
    return ret;
}

bool isUpper(string const & s) {
    for(char c : s) {
        if(!isupper(c)) return false;
    }
    return true;
}

int getOrAddIndex(string const & label) {
    auto it = labels.find(label);
    if(it != labels.end()) return it->second;
    int index = nodes.size();
    labels[label] = index;
    nodes.push_back(Node());
    nodes[index].visits = isUpper(label) ? INT_MIN : 0;
    return index;
}

int main() {
    int start = getOrAddIndex("start");
    int end = getOrAddIndex("end");

    string line, fromString, toString;
    while(cin >> line) {
        istringstream iss(line);
        getline(iss, fromString, '-');
        iss >> toString;
        int from = getOrAddIndex(fromString);
        int to = getOrAddIndex(toString);
        nodes[from].edges.push_back(to);
        nodes[to].edges.push_back(from);
    }
    printf("%d\n", solve(start, end));
}