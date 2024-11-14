/* Name: Robby Lawrence
Lab: Bitmatrix
NetID: rlawren9
Student ID: 000691931
Description: program acts as an interface to manipulate, display, and store
matrices that only have 0's and 1's as entries.
*/
#include <cstddef>
#include <iostream>
#include "bitmatrix.hpp"
#include <fstream>
#include <algorithm>
using namespace std;

Bitmatrix::Bitmatrix(int rows, int cols) {
    // error checking
    if (rows <= 0) {
        throw "Bad rows";
    }
    if (cols <= 0) {
        throw "Bad cols";
    }
   M.resize(rows,string(cols,'0')); // resize the vector and make each element a string of zeroes cols long
}

Bitmatrix::Bitmatrix(const string &fn) {
   ifstream fout(fn);
   string line;
   if (!fout.is_open()) {
       throw "Can't open file";
   }
   while (getline(fout, line)) {
     if (line.empty()) {
       continue; // skip the processing when the line is empty
     }
     for (size_t i = 0;i<line.size();i++) { // for every character in the line, check if it's 0, 1, or a space
       char character = line[i];
       if (character != '0' && character != '1' && character != ' ') {
         throw "Bad file format";
       }
     }
     line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end()); // iterate through line and erase the line if it's all spaces
     M.push_back(line);
   }
   fout.close();
}

bool Bitmatrix::Write(const string &fn)const {
    // error checking
   if (M.empty()) {
       return false;
   }
   ofstream fout(fn);
   if(!fout.is_open()) { // make sure that fout opened the file
       return false;
   }
   for (size_t i = 0; i < M.size(); i++) { // output the file
     fout << M[i] << endl;
   }
   fout.close();
   return true;
}

Bitmatrix *Bitmatrix::Copy()const {
   if (M.empty()) { // return NULL if we've got an empty string vector
       return NULL;
   }
   Bitmatrix* copy = new Bitmatrix(Rows(), Cols()); // create a pointer to a new bitmatrix with the same size
   for(size_t i = 0; i < M.size(); i++) {
     copy->M[i] = M[i]; // dereference and copy exactly as is
   }
   return copy;
}

void Bitmatrix::Print(size_t w)const {
   int counter_1 = 0;
   int counter_2 = 0;
   if (w < 0) { // error check
       throw "Bad value for W";
   }
   else if (w == 0) { // first handle the case when w = 0
     for (int i = 0; i < Rows(); i++) {
       for (int j = 0; j < Cols(); j++) {
         cout << M[i][j];
       }
     cout << endl;
     }
   }
   else { // then we can handle the case when w actually plays a part in the code
     for (int i = 0; i < Rows(); i++) {
       for (int j = 0; j < Cols(); j++) {
         counter_1++;
         cout << M[i][j];
         if (counter_1 == w) { // exit out of the loop
           if (j == Cols() - 1) {
             counter_1 = 0; // reset the counter
             break;
           }
           counter_1 = 0;
           cout << " ";
         }
       }
       cout << endl;
       counter_2 ++;
       counter_1 = 0;
       if (counter_2 == w) {
         if (i == Rows() - 1) { // when i is at the end of the rows
           break;
         }
         counter_2 = 0; // reset the counter
         cout << endl;
       }
     }
   }
}


bool Bitmatrix::PGM(const string &fn, int p, int border)const {
// do some math to figure out how big the picture should actually be
 int side_1 = Cols() * p + (Cols() + 1) * border;
 int side_2 = Rows() * p + (Rows() + 1) * border;
 ofstream fout(fn);
 if (!fout.is_open()) { // error check
   return false;
 }
 fout << "P2\n" << side_1 << " " << side_2 << '\n' << 255 << '\n'; // output the header so the PGM file actually works

 for (int i = 0; i < side_2; ++i) {
   for (int j = 0; j < side_1; ++j) {
     bool check = (j % (p + border) < border)||(i % (p + border) < border); // checks if the current position should be black
     if (check) {
       fout << "0 "; // 0 is black
     }
     else {
       int current_row = (i - border) / (p + border);
       int current_col = (j - border) / (p + border);
       if (current_col < Cols() && current_row < Rows()) {
         if (Val(current_row, current_col) == '0') {
           fout << "255 "; // make the output white when the string has a zero
         } else {
           fout << "100 "; // otherwise we can output a gray square
         }
       } else {
         fout << "0 "; // in the third case (which is the only one left over) we output white
       }
     }
   }
   fout << "\n"; // output a newline after each row to match what the correct output looks like
 }
 fout.close();
 return true;
}

int Bitmatrix::Rows()const { // self-explanatory
   return M.size();
}

int Bitmatrix::Cols()const { // also self-explanatory
   return M[0].size();
}

char Bitmatrix::Val(int row, int col)const {
   if (row < 0 || col < 0 || row > Rows() || col > Cols()) {
       return 'x'; // return 'x' if error checking isn't good
   }
   return M[row][col]; // else return the char in the correct element
}

bool Bitmatrix::Set(int row, int col, char val) {
   if (val != '0' && val != '1' && val != 1 && val != 0) { // error checking
       return false;
   } else { // if we pass error checking, just set the element to the parameter provided
     M[row][col] = val;
   }
   return true;
}

bool Bitmatrix::Swap_Rows(int r1, int r2) {
   if (r1 < 0 || r2 < 0  || r1 > Rows() || r2 > Rows()) { // error checking
       return false;
   }
   vector <string> intermediate = M; // gotta store one of the elements so it's not lost
   M[r1] = intermediate[r2];
   M[r2] = intermediate[r1]; // swap the elements
   return true;
}


bool Bitmatrix::R1_Plus_Equals_R2(int r1, int r2) {
   int number = 0;
   if (r1 < 0 || r1 > Rows() || r2 < 0 || r2 > Rows()) { // error checking
       return false;
   }
   for (int i = 0; i < Cols(); i++) {
     number = (int(M[r1][i]) + int(M[r2][i])) % 2; // make sure the number is 0 or 1
     M[r1][i] = (char)(number + 48); // ensure that the final number is a char instead of an int
   }
   return true;
}

Bitmatrix *Sum(const Bitmatrix *a1, const Bitmatrix *a2) {
 int dummy = 0; // variable to keep track of the sum
 if (a1->Rows() != a2->Rows() || a1->Cols() != a2->Cols()) { // error checking
     return NULL;
 }
 Bitmatrix *sum = new Bitmatrix(a1->Rows(), a1->Cols());
  for (int i = 0; i < a1->Rows(); i++) { // go through the matrices and add each entry then take that modulo 2
   for (int j = 0; j < a1->Cols(); j++) {
     dummy = (int(a1->Val(i, j)) + int(a2->Val(i, j))) % 2;
     sum->Set(i, j, (char)(dummy + 48)); // typecast from integer to char
   }
  }
 return sum;
}


Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2) {
 if (a1->Cols() != a2->Rows()) { // error checking
   return NULL;
 }
 Bitmatrix *product = new Bitmatrix(a1->Rows(), a2->Cols()); // create a new matrix that will hold the new entries in it
 for (int i = 0; i < a1->Rows(); i++) {
   for (int j = 0; j < a2->Cols(); j++) {
     int dummy = 0; // variable that can hold each entry in it before
     for (int k = 0; k < a1->Cols(); k++) {
       dummy += (a1->Val(i, k) - '0') * (a2->Val(k, j) - '0');
     }
     product->Set(i, j, (dummy % 2) + '0'); // set the intersection of the ith row and the jth column to the calculated value
   }
 }
 return product;
}

Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const vector <int> &rows) {
 Bitmatrix *output = new Bitmatrix(rows.size(), a1->Cols());
 for (size_t i = 0; i < rows.size(); i++) {
   if (rows[i] >= a1->Rows() || rows[i] < 0) { // error check
     delete output; // deallocate the memory
     return NULL;
   }
   for (int j = 0; j < a1->Cols(); j++) {
     output->Set(i, j, a1->Val(rows[i], j)); // say hi if you see this comment!
   }
 }
 return output;
}

Bitmatrix *Inverse(const Bitmatrix *m) {
 if (m->Cols() != m->Rows()) { // error check
     return NULL;
 }
 int side = m->Rows();
 Bitmatrix *inverse = new Bitmatrix(side, side); // create an empty r by r bitmatrix
 Bitmatrix *original_matrix = m->Copy(); // create a copy of the original bitmatrix
 for (int i = 0; i < side; i++) {
   inverse->Set(i, i, '1'); // set the intersection of the ith row and ith column to 1
 }
 for (int k = 0; k < side; k++) {
   if (original_matrix->Val(k, k) == '0') { // iterate through the matrix
     bool val = false; // keep track if it worked or not
     for (int j = k + 1; j < side; j++) {
       if (original_matrix->Val(j, k) == '1') {
         val = true;
         original_matrix->Swap_Rows(k, j);
         inverse->Swap_Rows(k, j);
         break;
       }
     }
     if (!val) { // unsuccessful, matrix is uninvertible
       delete original_matrix; // deallocate the memory and return NULL
       delete inverse;
       return NULL;
     }
   }
   for (int j = k + 1; j < side; j++) {
     if (original_matrix->Val(j, k) == '1') { // if the value at the intersection of the jth
         // row and the kth column is 1, add those rows in both matrices
       original_matrix->R1_Plus_Equals_R2(j, k);
       inverse->R1_Plus_Equals_R2(j, k);
     }
   }
 }
 for (int i = 0; i < side;i++) { // iterate through the original matrix and add the rows when there's a 1
   for (int j = 0; j < i;j++) {
     if (original_matrix->Val(j, i) == '1') {
        inverse->R1_Plus_Equals_R2(j, i);
        original_matrix->R1_Plus_Equals_R2(j, i);
     }
   }
 }
 delete original_matrix; // deallocate memory
 return inverse;
}

BM_Hash::BM_Hash(int size) {
 if (size <= 0) { // error check
     throw "Bad size";
 }
 Table.resize(size); // setup the table
}

bool BM_Hash::Store(const string &key, Bitmatrix *bm) {
 // djbhash handed down from the TAs
 unsigned int h;
 h = 5381;
 for (size_t i = 0; i < key.size(); i++) { // no idea how this works lol
   h = (h << 5) + h + key[i];
 }
 for (int i = 0; i < Table.size(); i++) { // iterate through the table
   for (int j = 0; j < Table[i].size(); j++) {
     if (Table[i][j].key == key) { // if the key for another entry matches this entry,
         // return false
         return false;
     }
   }
 }
 HTE new_entry; // create a new entry for the matrix we're storing
 new_entry.key = key; // give the new entry it's key and value, in this case the matrix
 new_entry.bm = bm;
 Table[h % Table.size()].push_back(new_entry); // ensure that the entry is within the correct bounds
 // then add it to the table
 return true;
}

Bitmatrix *BM_Hash::Recall(const string &key) const { // this is our find function
  for (int i = 0; i < Table.size(); i++) { // iterate through the table looking for the key
   for (int j = 0; j < Table[i].size(); j++) {
     if (Table[i][j].key == key) { // if we find the key, return the corresponding bitmatrix
         return Table[i][j].bm;
     }
   }
 }
 return NULL; // if we can't find the entry, return NULL
}

vector<HTE> BM_Hash::All() const { // return all of the hash table entries
 vector<HTE> result;
 for (size_t i = 0; i < Table.size(); i++) { // iterate through the table and add each entry to the vector
   for (size_t j = 0; j < Table[i].size(); j++) {
     result.push_back(Table[i][j]);
   }
 }
 return result;
}
