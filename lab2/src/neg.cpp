#include <iostream>
#include <vector>
using namespace std;

int main() {
    int num,columns,rows,dummy;
    // ignore "P2", get columns and rows, ignore 255
    string word;
    // ERROR CHECKING HEADER
    cin >> word;
    if (word != "P2") {
        cerr << "Bad PGM file -- first word is not P2" << endl;
        return 1;
    }
    if (!(cin >> columns)) {
        cerr << "Bad PGM file -- No column specification" << endl;
    }
    if (columns < 0) {
        cerr << "Bad PGM file -- No column specification" << endl;
        return 1;
    }
    if (!(cin >> rows)) {
        cerr << "Bad PGM file -- No row specification" << endl;
    }
    if (rows < 0) {
        cerr << "Bad PGM file -- No row specification" << endl;
        return 1;
    }
    cin >> dummy;
    if (dummy != 255) {
        cerr << "Bad PGM file -- No 255 following the rows and columns" << endl;
        return 1;
    }
    // counter to keep track of current pixel
    int counter = 0;
    int negative;
    // output header
    cout << "P2" << endl << columns << " " << rows << endl << 255 << endl;
    // read the file and output as you go
    for (int row = 1;row<=columns;row++) {
        for (int column = 1;column<=rows;column++) {
            cin >> num;
            if (!(num <= 255 && num >=0)) {
                cerr << "Bad PGM file -- pixel " << counter << " is not a number between 0 and 255" << endl;
                return 1;
            }
            // the negative of any pixel is just 255 - value
            negative = 255 - num;
            // output the number and a newline
            cout << negative << endl;
            counter++; // increment the counter
        }
    }
    return 0;
}
