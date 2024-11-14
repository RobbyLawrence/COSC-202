#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    // error check command line arguments
    if (argc != 3) {
        cerr << "usage: graycard rows cols" << endl;
        return 1;
    }

    // stringstream to error check c-style strings in argv[]
    istringstream sin;

    // move command line arguments into integer variables
    sin.str(argv[1]);
    int rows,columns;
    if (!(sin >> rows)) {
        cerr << "usage: graycard rows cols" << endl;
        return 1;
    }

    sin.clear();
    sin.str(argv[2]);
    if (!(sin >> columns)) {
        cerr << "usage: graycard rows cols" << endl;
        return 1;
    }

    // error check columns and rows
    if (rows <= 0) {
        cerr << "usage: graycard rows cols" << endl;
        return 1;
    }
    if (columns <= 0) {
        cerr << "usage: graycard rows cols" << endl;
    }
    if (rows % 3 != 0) {
        cerr << "rows must be a multiple of three" << endl;
        return 1;
    }

    // start actually printing the file to standard output
    // header
    cout << "P2" << endl;
    cout << columns << " " << rows << endl << 255 << endl;
    // output pixels
    for (int row = 0;row<rows;row++) {
        for (int column = 0;column<columns;column++) {
            if (row < rows/3) {
                cout << 0 << " ";
            }
            else if (row >= rows/3 && row < 2 * (rows/3)) {
                cout << 209 << " ";
            }
            else if (row >= (2 * rows/3)) {
                cout << 255 << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
