#include <iostream>
#include <sstream>
using namespace std;

int main() {
  stringstream ss;
  int num;
  ss << hex << "a000000";
  ss >> num;
}
