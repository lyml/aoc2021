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

typedef long long ll;

struct Packet {
    ll version;
    ll typeId;
    ll lengthType;
    vector<Packet> subPackets;
    ll literal;
};

ll take(vector<ll> & bits, ll & o, ll count) {
    //printf("taking %lld from %lld\n", count, o);
    ll ret = 0;
    ll orig = o;
    for(ll i = 0; i < count; ++i) {
        ret = (ret << 1)|bits[o++];
    }
    // printf("bit [%lld, %lld[ = ", orig, o);
    // for(ll i = orig; i < o; ++i) {
    //     printf("%lld", bits[i]);
    // }
    // printf(" = %lld\n", ret);
    return ret;
}

Packet parsePacket(vector<ll> & bits, ll & o) {
    Packet ret;
    ret.version = take(bits, o, 3);
    ret.typeId = take(bits, o, 3);
    //return make_tuple(ret, 0);
    if(ret.typeId == 4) {
        // printf("is literal at %lld: ", o);
        ll group = 0;
        ll num = 0;
        do {
            group = take(bits, o, 5);
            num = (num << 4)|(group&0xf);
        } while(group&(1<<4));
        ret.literal = num;
        // printf("%lld\n", num);
        return ret;
    }
    ret.lengthType = take(bits, o, 1);
    if(ret.lengthType == 0) {
        ll length = take(bits, o, 15);
        ll end = o + length;

        while(o < end) {
            // usleep(1000000);
            ret.subPackets.push_back(parsePacket(bits, o));
        }
    }
    else {
        ll subPackets = take(bits, o, 11);
        for(ll i = 0; i < subPackets; ++i) {
            ret.subPackets.push_back(parsePacket(bits, o));
        }
    }

    return ret;
}

void pushHex(vector<ll> & bits, char c) {
    ll val = 0;
    if(c >= '0' && c <= '9') val = c - '0';
    else val = c - 'A' + 10;
    for(ll i = 0; i < 4; ++i) {
        bits.push_back((val&0x8) ? 1 : 0);
        val = val << 1;
    }
}

ll dfs(Packet const & p) {
    if(p.typeId == 0) {
        ll sum = 0;
        for(auto & p2 : p.subPackets) sum += dfs(p2);
        // printf("sumpacket: %lld\n", sum);
        return sum;
    }
    else if(p.typeId == 1) {
        ll prod = 1;
        for(auto & p2 : p.subPackets) prod *= dfs(p2);
        // printf("prodpacket: %lld\n", prod);
        return prod;
    }
    else if(p.typeId == 2) {
        ll minVal = dfs(p.subPackets[0]);
        for(auto & p2 : p.subPackets) minVal = min(minVal, dfs(p2));
        // printf("minval: %lld\n", minVal);
        return minVal;
    }
    else if(p.typeId == 3) {
        ll maxVal = dfs(p.subPackets[0]);
        for(auto & p2 : p.subPackets) maxVal = max(maxVal, dfs(p2));
        // printf("maxval: %lld\n", maxVal);
        return maxVal;
    }
    else if(p.typeId == 4) {
        // printf("literal: %lld\n", p.literal);
        return p.literal;
    }
    else if(p.typeId == 5) {
        return dfs(p.subPackets[0]) > dfs(p.subPackets[1]) ? 1 : 0;
    }
    else if(p.typeId == 6) {
        return dfs(p.subPackets[0]) < dfs(p.subPackets[1]) ? 1 : 0;
    }
    else {
        return dfs(p.subPackets[0]) == dfs(p.subPackets[1]) ? 1 : 0;
    }
}

int main() {
    string hex;
    cin >> hex;
    vector<ll> bits;
    for(ll i = 0; i < hex.size(); ++i) {
        pushHex(bits, hex[i]);
    }
    // for(ll i = 0; i < bits.size(); ++i) {
    //     printf("%lld", bits[i]);
    // }
    // printf("\n");
    ll o = 0;
    auto packet = parsePacket(bits, o);

    ll sum = dfs(packet);
    printf("%lld\n", sum);
}