#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int num,columns,rows,dummy;
    double total = 0;
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
    // counter is to keep track of current pixel
    int counter = 0;
    for (int row = 0;row<rows;row++) {
        for (int column = 0;column<columns;column++) {
            cin >> num;
            // error check pixel
            if (!(num <= 255 && num >=0)) {
                cerr << "Bad PGM file -- pixel " << counter << " is not a number between 0 and 255" << endl;
                return 1;
            }
            // add to total and increment counter
            total += num;
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
    // decided to use cout instead of printf, TA's said it was okay to do either
    //
    printf("# Rows:%12d\n",rows);
    printf("# Columns:%9d\n",columns);
    printf("# Pixels:%10d\n",rows*columns);
    printf("Avg Pixel:%9.3f\n",total/(rows*columns));
    return 0;
}
