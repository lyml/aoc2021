#include <iostream>
#include <string>

using namespace std;

int main() {
    string dir;
    int val;
    int x = 0, y = 0;
    while(cin >> dir >> val) {
        if(dir == "forward") {
            x += val;
        }
        else if(dir == "up") {
            y -= val;
        }
        else if(dir == "down") {
            y += val;
        }
        if( y < 0) {
            cout << "negative y" << endl;
        }
    }
    printf("%d * %d = %d", x, y, x*y);
}