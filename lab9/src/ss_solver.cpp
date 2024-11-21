/* Name: Robby Lawrence
   Student ID: 000691931
   NetID: rlawren9
   Lab: ShapeShifter Solver
   Description: solves a given shapeshifter game
*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

void place_shape(vector<string> &grid, vector<string> &shape, int row, int column) { // places a shape
  int rows = shape.size();
  int cols = shape[0].size(); // initial column size
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (shape[i][j] == '1') {
        if (grid[row + i][column + j] == '1') { // flip bit
          grid[row + i][column + j] = '0';
        }
        else {
          grid[row + i][column + j] = '1';
        }
      }
    }
  }
}

bool test_ones(vector<string> &grid) { // check if the grid is ones
  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] != '1') {
        return false;
      }
    }
  }
  return true;
}

void undo(vector<string> &grid, vector<string> &shape, int row, int col) {
  place_shape(grid, shape, row, col); // reapply the shape to undo
}

bool solve_game(vector<string> &grid, vector<vector<string> > &shapes, int s_index, vector<int> &positions_row, vector<int> &p_col) {
  if ((size_t)s_index == shapes.size()) { // base case
    return test_ones(grid);
  }
  vector<string> &shape = shapes[s_index]; // current shape and size
  int s_rows = shape.size();
  int s_columns = shape[0].size();
  int g_rows = grid.size();
  int g_columns = grid[0].size();
  for (int i = 0; i <= g_rows - s_rows; i++) { // try positions
    for (int j = 0; j <= g_columns - s_columns; j++) {
      place_shape(grid, shape, i, j); // apply shape
      positions_row.push_back(i);
      p_col.push_back(j);
      if (solve_game(grid, shapes, s_index + 1, positions_row, p_col)) { // recurse to next, return good if it worked
        return true;
      }
      undo(grid, shape, i, j); // undo if the application didn't work
      positions_row.pop_back();
      p_col.pop_back();
    }
  }
  return false; // no good spot
}

int main(int argc, char *argv[]) {
  if (argc == 1) { // error if there aren't cmd lines args
    cerr << "Usage: ss_solver grid_row1 [grid_row2 ...]" << endl;
    return 1;
  }
  vector<string> grid; // read in the grid
  for (int i = 1; i < argc; i++) {
    grid.push_back(argv[i]);
  }
  size_t rows = grid.size(); // initialize variables
  size_t columns = grid[0].size();
  for (size_t i = 0; i < rows; i++) {
    if (grid[i].size() != columns) {
      cerr << "Each rows must have the same size." << endl;
      return 1;
    }
  }
  vector<vector<string> > shapes; // read in the shapes
  string line;
  while (getline(cin, line)) {
    istringstream sin(line); // use sstream to change line into words
    string word;
    vector<string> shape;
    while (sin >> word) { // add words to shape vector
      shape.push_back(word);
    }
    if (!shape.empty()) { // make sure all s_cols are same size
      for (size_t i = 0; i < shape.size(); i++) {
        if (shape[i].size() != shape[0].size()) {
          cerr << "All shape rows must have the same length." << endl;
          return 1;
        }
      }
      shapes.push_back(shape);
    }
  }
  vector<int> p_row;
  vector<int> p_column;
  if (solve_game(grid, shapes, 0, p_row, p_column)) {
    for (size_t i = 0; i < shapes.size(); i++) { // output solution and shapes
      vector<string> &shape = shapes[i];
      for (size_t i = 0; i < shape.size(); i++) {
        cout << shape[i] << " ";
      }
      int row = p_row[i]; // output
      int col = p_column[i];
      cout << row << " " << col << endl;
    }
  }
  return 0;
}
