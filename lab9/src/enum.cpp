#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void do_enumeration(string &s, int index, int n_ones) {
    if (n_ones < 0) return; // Can't have negative ones
    if (n_ones > s.size() - index) return; // Not enough positions left
    if (index == s.size()) {
        if (n_ones == 0) {
            cout << s << endl;
        }
        return;
    }
    // If we must place ones in all remaining positions
    if (n_ones == s.size() - index) {
        for (int i = index; i < s.size(); ++i) {
            s[i] = '1';
        }
        cout << s << endl;
        return;
    }
    // If no ones left, fill with zeros
    if (n_ones == 0) {
        for (int i = index; i < s.size(); ++i) {
            s[i] = '0';
        }
        cout << s << endl;
        return;
    }
    // Place '0' and recurse
    s[index] = '0';
    do_enumeration(s, index + 1, n_ones);
    // Place '1' and recurse
    s[index] = '1';
    do_enumeration(s, index + 1, n_ones - 1);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: bin/enum length ones" << endl;
        return 1;
    }
    int length = atoi(argv[1]);
    int ones = atoi(argv[2]);
    if (length < 0 || ones < 0 || ones > length) {
        cerr << "Invalid arguments" << endl;
        return 1;
    }
    string s(length, '-'); // Initialize string of length 'length' with '-'
    do_enumeration(s, 0, ones);
    return 0;
}

