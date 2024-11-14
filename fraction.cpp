/* Name: Robby Lawrence
 * NetID: rlawren9
 * StudentID: 000691931
 * Lab: Keno A
 * Description: implements the Fraction class, providing methods to manipulate a fraction.
 * */
#include <iostream>
#include <set>
#include <vector>
#include "fraction.hpp"
using namespace std;

void Fraction::Clear() { // void function just clears both multisets
  numerator.clear();
  denominator.clear();
}

bool Fraction::Multiply_Number(int n) { // add a number to the numerator
  if (n <= 0) { // error checking
    return false;
  }
  if (n == 1) {
    return true;
  }
  multiset<int>::iterator it;
  it = denominator.find(n);
  if (it != denominator.end()) { // if n is in the denominator
    denominator.erase(it);
    return true;
  }
  else {
    numerator.insert(n);
    return true;
  }
}

bool Fraction::Divide_Number(int n) { // check if n is in the numerator set, delete if so; add to denominator if not
  if (n <= 0) { // error checking
    return false;
  }
  if (n == 1) {
    return true;
  }
  multiset<int>::iterator it;
  it = numerator.find(n);
  if (it != numerator.end()) { // if n IS in the numerator
    numerator.erase(it);
    return true;
  }
  else {
    denominator.insert(n);
    return true;
  }
}

bool Fraction::Multiply_Factorial(int n) {
  if (n <= 0) { // error checking
    return false;
  }
  multiset<int>::iterator it;
  for (int i = n;i>1;i--) { // we're adding a bunch of numbers to the numerator
    it = denominator.find(i);
    if (it != denominator.end()) { // to save time, we search for the number in the denominator and erase it if it's in there
      denominator.erase(it);
      continue;
    }
    else {
      numerator.insert(i);
    }
  }
  return true;
}

bool Fraction::Divide_Factorial(int n) {
  if (n <= 0) {
    return false;
  }
  multiset<int>::iterator it;
  for (int i = n;i>1;i--) {
    it = numerator.find(i);
    if (it != numerator.end()) {
      numerator.erase(it);
      continue;
    }
    else {
      denominator.insert(i);
    }
  }
  return true;
}

bool Fraction::Multiply_Binom(int n, int k) { // we can use existing methods
  if (n <= 0 || k < 0) {
    return false;
  }
  Multiply_Factorial(n);
  Divide_Factorial(k);
  Divide_Factorial((n-k)); // we can use those formulas, and all the manipulating and canceling is done for us
  return true;
}

bool Fraction::Divide_Binom(int n, int k) { // this method is the same as multiplying by the reciprocal of the previous method
  if (n <= 0 || k < 0) {
    return false;
  }
  Divide_Factorial(n);
  Multiply_Factorial(k);
  Multiply_Factorial(n-k);
  return true;
}

void Fraction::Invert() { // we need to swap the numerator and the denominator, but need to hold one of them so not to lose any data
  // we'll use a vector to store all values of the numerator
  vector<int> holding;
  multiset<int>::iterator it;
  for (it = numerator.begin();it != numerator.end();it++) {
    holding.push_back(*it); // dereference the iterator and add it to the end of the vector
  }
  // we've got the numerator elements in holding now, so we throw the denominator in numerator
  numerator.clear();
  for (it = denominator.begin();it != denominator.end();it++) {
    numerator.insert(*it); // insert each element of denominator into the numerator
  }
  
  denominator.clear();
  for (size_t i = 0;i < holding.size();i++) {
    denominator.insert(holding[i]); // insert each element in holding in the denominator
  }
}

void Fraction::Print() const {
  multiset<int>::iterator it;
  size_t counter = 0;
  for (it = numerator.begin();it != numerator.end();it++) {
    cout << *it;
    if (counter < (numerator.size()-1)) { // print a " * " when there are more than just one element in the multiset
      cout << " * ";
    }
    counter++;
  }
  if (numerator.empty()) {
    cout << "1"; // print out a one in case the numerator is empty
  }
  counter = 0;
  for (it = denominator.begin();it != denominator.end();it++) {
    if (counter < denominator.size()) { // print out " / " when necessary
      cout << " / ";
    }
    cout << *it;
  }
  cout << endl;
}

double Fraction::Calculate_Product() const {
  multiset<int>::iterator it;
  double product = 1;
  for (it = numerator.begin();it != numerator.end();it++) { // multiply product by everything in numerator
    product *= (*it);
  }
  for (it = denominator.begin();it != denominator.end();it++) { // divide product by everything in denominator
    product /= (*it);
  }
  return product;
}
