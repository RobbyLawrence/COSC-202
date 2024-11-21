/* Name: Robby Lawrence
   Student ID: 000691931
   NetID: rlawren9
   Lab: Enumerating Strings
   Description: enumerates all strings of a specific length with a certain number of ones and zeroes
*/
#include <iostream>
#include <string>
using namespace std;

void enumerator(string &str, int current_index, int number_ones) {
    if (number_ones < 0) { // error checking
        return;
    }
    if ((size_t)number_ones > str.size() - current_index) { // terminate if there aren't enough spots left
        return;
    }
    if ((size_t)current_index == str.size()) { // output or terminate if done
        if (number_ones == 0) {
            cout << str << endl;
        }
        return;
    }
    if (number_ones == 0) { // place zeroes in all spots
        for (size_t i = current_index; i < str.size(); ++i) {
            str[i] = '0';
        }
        cout << str << endl;
        return;
    }
    if ((size_t)number_ones == str.size() - current_index) { // place ones in all spots
        for (size_t i = current_index; i < str.size(); ++i) {
            str[i] = '1';
        }
        cout << str << endl;
        return;
    }
    str[current_index] = '0'; // put a zero in next spot and recurse
    enumerator(str, current_index + 1, number_ones);
    str[current_index] = '1'; // put a one in the next spot and recurse
    enumerator(str, current_index + 1, number_ones - 1);
}
int main(int argc, char** argv) {
    if (argc != 3) { // error check
        cerr << "Usage: bin/enum length ones" << endl;
        return 1;
    }
    int length = atoi(argv[1]); // make command line args usable
    int number_ones = atoi(argv[2]);
    if (length < 0 || number_ones < 0 || number_ones > length) { // error check
        cerr << "Invalid arguments" << endl;
        return 1;
    }
    string s(length, '-'); // put dashes in all the string's characters
    enumerator(s, 0, number_ones); // run function
    return 0;
}
