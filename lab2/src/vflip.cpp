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
        return 1;
    }
    if (columns <= 0) {
        cerr << "Bad PGM file -- No column specification" << endl;
        return 1;
    }
    if (!(cin >> rows)) {
        cerr << "Bad PGM file -- No row specification" << endl;
        return 1;
    }
    if (rows <= 0) {
        cerr << "Bad PGM file -- No row specification" << endl;
        return 1;
    }
    cin >> dummy;
    if (dummy != 255) {
        cerr << "Bad PGM file -- No 255 following the rows and columns" << endl;
        return 1;
    }
    // initialize vector of vectors
    vector<vector<int> > pixel_matrix(rows, vector<int>(columns,0));
    // counter is to keep track of current pixel
    int counter = 0;
    for (int row = 0;row<rows;row++) {
        for (int column = 0;column<columns;column++) {
            if (!(cin >> num)) {
                cerr << "Bad PGM file -- pixel " << counter << " is not a number between 0 and 255" << endl;
                return 1;
            }
            if (!(num <= 255 && num >=0)) {
                cerr << "Bad PGM file -- pixel " << counter << " is not a number between 0 and 255" << endl;
                return 1;
            }
            pixel_matrix[row][column] = num;
            counter++;
        }
    }
    char check = '\n';
    // check for extra stuff after 
    if (cin >> check) {
        if (check != '\n') {
            cerr << "Bad PGM file -- Extra stuff after the pixels" << endl;
            return 1;
        }
    }
    // print header to standard output
    cout << "P2\n" << columns << " " << rows << endl << 255 << endl;
    for (int row = rows-1; row >= 0; row--) {
        for (int column = 0; column < columns; column++) {
            cout << pixel_matrix[row][column] << endl;
            counter++;
        }
    }
    return 0;
}
