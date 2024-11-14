/* Name: Robby Lawrence
 * NetID: rlawren9
 * StudentID: 000691931
 * Lab: Keno B
 * Description: provides a use for the Fraction class by calculating expected returns for the game Keno
*/
#include <iostream>
#include <vector>
#include "fraction.hpp"
using namespace std;
int main() {
  Fraction fraction;
  double bet_amount = 0; // first number
  double payout = 0; // second number in pairs
  double probability = 0;
  double rpb = 0; // return per bet
  int num_caught = 0; // first number in pairs
  int num_balls = 0; // second number
  cin >> bet_amount >> num_balls;
  vector<int> catches;
  vector<double> payouts;
  fraction.Clear();
  // starting output
  printf("Bet: %.2lf\n",bet_amount);
  cout << "Balls Picked: " << num_balls << endl;
  
  while (cin >> num_caught >> payout) { // load vectors
    catches.push_back(num_caught);
    payouts.push_back(payout);
  }

  for (size_t i = 0;i<catches.size();i++) {
    fraction.Multiply_Binom(80-num_balls,20-catches[i]);
    fraction.Multiply_Binom(num_balls,catches[i]);
    fraction.Divide_Binom(80,20);
    probability = fraction.Calculate_Product();
    cout << "  Probability of catching " << catches[i] << " of " << num_balls << ": " << probability << " -- Expected return: " << payouts[i]*probability << endl;
    rpb += (payouts[i]*probability); // add the expected return to rpb 
    fraction.Clear();
  }
  rpb -= bet_amount;
  printf("Your return per bet: %.2lf\n",rpb);
  printf("Normalized: %.2lf\n",rpb/bet_amount);
  return 0;
}
