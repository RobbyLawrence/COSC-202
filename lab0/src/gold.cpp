#include <iostream>
using namespace std;

int main() {
    char letter = 95;
    int total_gold = 0;
    while (cin >> letter) {
        if (letter >= 65 && letter <= 90) {
            total_gold += (letter - 64);
        }
    }
    cout << total_gold << endl;
    return 0;
}
