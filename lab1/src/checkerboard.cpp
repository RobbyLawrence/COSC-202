// Name: Robert Lawrence
// Student ID: 000691931
// Lab 1: Checkerboard
#include <iostream>
using namespace std;
// function for checkerboard with 5 parameters
void checkerboard(int rows, int columns, char sc, int cycle_size, int width) {
    // for the number of rows
    for (int r = 0; r < rows; ++r) {
        // for the width
            for (int w = 0; w < width; ++w) {
            // for the columns
                for (int c = 0; c < columns; ++c) {
                // increase the character, using modulo in case of repeats
                    char current = sc + (r + c) % cycle_size;
                    for (int wc = 0; wc < width; ++wc) {
                        // print the character
                        cout << current;
                    }
                }
            // after all the characters in a row, print a newline
                cout << endl;
            }
        }
}

int main() {
    // initialize variables
    int rows, columns, cycle_size, width;
    char sc;
    // error check
    if (!(cin >> rows >> columns >> sc >> cycle_size >> width)) {
        cerr << "usage: checkerboard  - stdin should contain R, C, SC, CS and W" << endl;
        return 1;
    }
    else if (rows <= 0 || columns <= 0 || (int(sc + cycle_size)) > 127 || cycle_size <= 0 || width <= 0) {
        return 1;
    }
    // if all conditions pass, run the function
    else {
        checkerboard(rows, columns, sc, cycle_size, width);
    }
    return 0;
}
