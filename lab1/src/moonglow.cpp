// Name: Robert Lawrence
// Student ID: 000691931
// Lab 1: Moonglow
#include <iostream>
using namespace std;

int main() {
    // initialize variables
    string name,word;
    double current_num, score;
    double total = 0;
    score = 0;
    int counter = 0;
    // loop for cin to search for the end of the file
    while(!cin.eof()) {
        // if it's a number, add it to the score
        if (cin >> current_num) {
            score += current_num;
            continue;
        }
        else {
            // clear fail bit, put the string into 'word'
            cin.clear();
            cin >> word;
            // check if word is "NAME", if so, take next word as name
            if (word == "NAME") {
                cin >> name;
                continue;
            }
            // check if word is "AVERAGE"
            if (word == "AVERAGE") {
                // loop to get all numbers after average
                while (cin >> current_num) {
                    total += current_num;
                    counter++; // counter to keep track of numbers
                }
                // NaN prevention
                if (counter > 0) {
                    score += (total / counter);
                }
                // reset total and counter, clear fail bit
                total = 0;
                counter = 0;
                cin.clear();
            }
        }
    }
    // output name and score
    cout << name << " " << score << endl;
    return 0;
}
