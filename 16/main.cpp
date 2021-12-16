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
#include <unistd.h>

using namespace std;

struct Packet {
    int version;
    int typeId;
    int lengthType;
    vector<Packet> subPackets;
    int literal;
};

int take(vector<int> & bits, int & o, int count) {
    //printf("taking %d from %d\n", count, o);
    int ret = 0;
    int orig = o;
    for(int i = 0; i < count; ++i) {
        ret = (ret << 1)|bits[o++];
    }
    // printf("bit [%d, %d[ = ", orig, o);
    // for(int i = orig; i < o; ++i) {
    //     printf("%d", bits[i]);
    // }
    // printf(" = %d\n", ret);
    return ret;
}

Packet parsePacket(vector<int> & bits, int & o) {
    Packet ret;
    ret.version = take(bits, o, 3);
    ret.typeId = take(bits, o, 3);
    //return make_tuple(ret, 0);
    if(ret.typeId == 4) {
        // printf("is literal at %d: ", o);
        int group = 0;
        int num = 0;
        do {
            group = take(bits, o, 5);
            num = (num << 4)|(group&0xf);
        } while(group&(1<<4));
        ret.literal = num;
        // printf("%d\n", num);
        return ret;
    }
    ret.lengthType = take(bits, o, 1);
    if(ret.lengthType == 0) {
        int length = take(bits, o, 15);
        int end = o + length;

        while(o < end) {
            // usleep(1000000);
            ret.subPackets.push_back(parsePacket(bits, o));
        }
    }
    else {
        int subPackets = take(bits, o, 11);
        for(int i = 0; i < subPackets; ++i) {
            ret.subPackets.push_back(parsePacket(bits, o));
        }
    }

    return ret;
}

void pushHex(vector<int> & bits, char c) {
    int val = 0;
    if(c >= '0' && c <= '9') val = c - '0';
    else val = c - 'A' + 10;
    for(int i = 0; i < 4; ++i) {
        bits.push_back((val&0x8) ? 1 : 0);
        val = val << 1;
    }
}

int dfs(Packet const & p) {
    int sum = p.version;
    for(Packet const & p2 : p.subPackets) {
        sum += dfs(p2);
    }
    return sum;
}

int main() {
    string hex;
    cin >> hex;
    vector<int> bits;
    for(int i = 0; i < hex.size(); ++i) {
        pushHex(bits, hex[i]);
    }
    // for(int i = 0; i < bits.size(); ++i) {
    //     printf("%d", bits[i]);
    // }
    // printf("\n");
    int o = 0;
    auto packet = parsePacket(bits, o);

    int sum = dfs(packet);
    printf("%d\n", sum);
}