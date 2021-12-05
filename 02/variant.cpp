#include <iostream>
#include <string>

using namespace std;

int main() {
    string dir;
    int val;
    int x = 0, y = 0, aim = 0;
    while(cin >> dir >> val) {
        if(dir == "forward") {
            x += val;
            y += aim * val;
        }
        else if(dir == "up") {
            aim -= val;
        }
        else if(dir == "down") {
            aim += val;
        }
        if( y < 0) {
            cout << "negative y" << endl;
        }
    }
    printf("%d * %d = %d\n", x, y, x*y);
}