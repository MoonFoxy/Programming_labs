#include <iostream>

using namespace std;

int main() {
    float X, Y;
    while(true) {
        cout << "Enter coordinates:\n";
        cin >> X >> Y;

        if ((X == 0) && (Y == 0)) {
            cout << "Stopped!\n";
            return 0;
        }

        if ((X >= 2 && X <= 6) && (Y <= X)) {
            cout << "Enters\n";
        } else {
            cout << "Excluded\n";
        }
    }
}
