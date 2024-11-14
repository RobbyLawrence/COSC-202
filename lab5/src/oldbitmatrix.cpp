/* Name: Robby Lawrence
 * NetID: rlawren9
 * Student ID: 000691931
 * Lab: Lab 5 - Bitmatrix
 * Description: This program allows the user to make and store matrices with entries zero and one,
 * while also allowing several operations on these matrices.
 * */
#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include "bitmatrix.hpp"
using namespace std;

Bitmatrix::Bitmatrix(int rows, int cols) {
  // error checks
  if (rows <= 0) {
    throw "Bad rows";
  }
  else if (cols <= 0) {
    throw "Bad cols";
  }
  else { // otherwise resizes the vector to store the correct number of strings
    M.resize(rows,string(cols,'0')); // resizes the vector, and fills each spot with strings of zeroes equal to the number of columns
  }
}

Bitmatrix::Bitmatrix(const string &fn) {

  // read in file
  ifstream fin(fn);

  // check is file open
  if (!fin.is_open())
    throw string("Can't open file");

  // read in file
  string line;
  int cols = -1; // track num of cols

  // read file line by line
  while (getline(fin, line)) {
    string row = "";

    // go through line and only accept 0 and 1
    for (size_t i = 0; i < line.size(); i++) {
      char ch = line[i];
      if (ch == '0' || ch == '1') {
        row += ch;
      } else if (ch != ' ' && ch != '\n' && ch != '\t') {
        throw string("Bad file format");
      }
    } // for loop closing

    if (row.empty())
      continue;

    if (cols == -1)
      cols = row.size();

    // check for correct length
    else if (row.size() != cols) {
      throw string("Bad file format");
    }

    // store
    M.push_back(row);
  }

  if (M.empty())
    throw string("Bad file format");

  fin.close();
}

// copy should be done; not sure if this is the intended method
Bitmatrix *Bitmatrix::Copy() const {
    Bitmatrix *copy = new Bitmatrix(Rows(),Cols());
    copy->M = M; // make the matrix the same
    return copy;
}
// write is hopefully done
bool Bitmatrix::Write(const string &fn) const {
    ofstream fout(fn);
    if (!fout.is_open()) {
        return false;
    }
    for (size_t i = 0;i<Rows();i++) {
        for (size_t j = 0;j<Cols();j++) {
            fout << M[i][j];
        }
        fout << endl;
    }
    return true;
}

void Bitmatrix::Print(size_t w) const {
    for (size_t i = 0;i < Rows();i++) {
        for (size_t j = 0;j < Cols();j++) {
            cout << M[i][j];
            if ((j+1)%w == 0 && j != M[i].size()-1) { // spaces
                cout << ' ';
            }
        }
        cout << endl;
        if ((i + 1)%w == 0 && i != M.size() - 1) { // blank lines
            cout << endl;
        }
    }
}

bool Bitmatrix::PGM(const string &fn, int p, int border) const
{
  (void) fn;
  (void) p;
  (void) border;
  return false;
}

int Bitmatrix::Rows() const {
  return M.size();
}

int Bitmatrix::Cols() const {
  return M[0].size();
}

// done?
char Bitmatrix::Val(int row, int col) const {
    if (M[row][col] != '0' && M[row][col] != '1') {
        return 'x';
    }
    else if (M[row][col] == '1') {
        return '1';
    }
    else {
        return '0';
    }
}

// set function isn't too bad
bool Bitmatrix::Set(int row, int col, char val) {
    if (val != '1' && val != '0') {
        return false;
    }
    if (row > Rows() || col > Cols() || row < 0 || col < 0) { // error check
        return false;
    }
    M[row][col] = val;
    return true;
}

// swap is done
bool Bitmatrix::Swap_Rows(int r1, int r2) {
  if (r1 < 0 || r2 < 0 || r1 > Rows() || r2 > Rows()) {
      return false;
  }
  swap(M[r1],M[r2]);
  return true;
}

bool Bitmatrix::R1_Plus_Equals_R2(int r1, int r2) {// we want to make it so we can add two rows of M
    if (r1 < 0 || r2 < 0 || r1 > Rows() || r2 > Rows()) { // error check parameters
        return false;
    }
    for (size_t i = 0;i<Cols();i++) {
        M[r1][i] = ((int)M[r1][i] + (int)M[r2][i]);
    }
    return true;
}


Bitmatrix *Sum(const Bitmatrix *a1, const Bitmatrix *a2) {
    (void)a1;
    (void)a2;
    return NULL;
}

Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2)
{
    // each entry is the dot product of the row and column that it's the intersection of
  (void) a1;
  (void) a2;
  return NULL;
}

Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const vector <int> &rows)
{
  (void) a1;
  (void) rows;
  return NULL;
}

Bitmatrix *Inverse(const Bitmatrix *m)
{
  (void) m;
  return NULL;
}



BM_Hash::BM_Hash(int size)
{
  (void) size;
}

bool BM_Hash::Store(const string &key, Bitmatrix *bm)
{
  (void) key;
  (void) bm;
  return false;
}

Bitmatrix *BM_Hash::Recall(const string &key) const
{
  (void) key;
  return NULL;
}

vector <HTE> BM_Hash::All() const
{
  vector <HTE> rv;

  return rv;
}
