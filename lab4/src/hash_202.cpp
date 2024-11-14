#include "hash_202.hpp"
#include <cstddef>
#include <ios>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <vector>
#include <sstream>
#include <iomanip>
// REMINDERS:
// We already have Keys as a vector of strings; it's empty to start out with
// Same for Vals, except Vals[i] is the value associated with Keys[i]
std:: string Hash_202::Set_Up(size_t table_size, const std::string &fxn, const std::string &collision) {
  if (!Keys.empty()) {
    return "Hash table already set up";
  }
  if (table_size <= 0) {
    return "Bad table size";
  }
  if (fxn != "Last7" && fxn != "XOR") {
    return "Bad hash function";
  }
  if (collision != "Linear" && collision != "Double") {
    return "Bad collision resolution strategy";
  }
  // resize the vectors in "protected:" to the correct size
  Keys.resize(table_size);
  Vals.resize(table_size);
  Nkeys = 0;

  // pick hash function
  if (fxn == "Last7") {
    Fxn = 'L'; // set the protected: Fxn to 76, stands for Last7
  } else {
    Fxn = 'X'; // set the protected: Fxn to 88, stands for XOR
  }

  // pick collision resolution strategy
  if (collision == "Linear") {
    Coll = 'L'; // sets Coll to 76
  } else {
    Coll = 'D'; // sets Coll to 68
  }
  // setup complete an empty string
  return "";
}

std::string Hash_202::Add(const std::string &key, const std::string &val) {
  // error checking inputs
  if (Keys.empty()) {
    return "Hash table not set up";
  }
  if (key.empty()) {
    return "Empty key";
  }
  for (size_t i = 0;i<key.length();i++) {
    if (key[i] != '0' && key[i] != '1' && key[i] != '2' && key[i] != '3' && key[i] != '4' && key[i] != '5'
      && key[i] != '6' && key[i] != '7' && key[i] != '8' && key[i] != '9' && key[i] !=
      'a' && key[i] != 'b' && key[i] != 'c' && key[i] != 'd' && key[i] != 'e' && key[i] != 'f') {
      return "Bad key (not all hex digits)";
    }
  }
  if (val.empty()) {
    return "Empty val";
  }
  if (Nkeys == Keys.size()) {
    return "Hash table full";
  }

  // variables for XOR hash
  std::string substring;
  std::vector<int> Substrings;
  int dummy;

  // hash Last7
  std::stringstream ss;
  std::string last_7;
  int index;
  int step_size;
  if (Fxn == 'L') {
    if (key.length() > 7) {
      last_7 = key.substr(key.length()-7,7);
    }
    else {
      last_7 = key;
    }
    // move the key into the string stream, output into the integer
    ss << std::hex << last_7;
    ss >> index;
    index = index % Keys.size();
  }
  // hash XOR
  else {
    // initalize some variables
    index = 0;
    // when the key is bigger than seven characters
    if (key.length() > 7) {
      for (size_t i = 0;i<(key.length()/7);i++) {
        substring = key.substr(0+7*i,7);
        ss << std::hex << substring;
        ss >> dummy;
        ss.ignore(10,'\n');
        ss.clear();
        Substrings.push_back(dummy);
      }
      // if the length of key is not a multiple of 7
      if (key.length() % 7 != 0) {
        substring = key.substr(key.length() - (key.length() % 7),key.length() % 7);
        ss << std::hex << substring;
        ss >> dummy;
        ss.ignore(10,'\n');
        ss.clear();
        Substrings.push_back(dummy);
      }
      for (int value : Substrings) {
        index ^= value;
      }
      index = index % Keys.size();
    } else {
      ss << std::hex << key;
      ss >> index;
      ss.ignore(10,'\n');
      ss.clear();
      index = index % Keys.size();
    }
  }
  if (Keys[index].empty()) {
    Keys[index] = key;
    Vals[index] = val;
    Nkeys++;
    return "";
  }
  // We've got the index now, but now we have to do collision resolution
  if (Coll == 'L') {
    // this is the actual linear implementation
    int counter = 1;
    while (true) {
      if (Keys[(index + counter) % Keys.size()].empty()) {
        Keys[(index + counter) % Keys.size()] = key;
        Vals[(index + counter) % Keys.size()] = val;
        Nkeys++;
        return "";
      }
      if (Keys[(index + counter) % Keys.size()] == key) {
        return "Key already in table";
      } 
      counter++; // increment the counter
    }
  }
  else { // When Coll == D
    if (Fxn == 'X') { // if the original hash function is XOR, use Last7 
      if (key.length() > 7) {
        last_7 = key.substr(key.length()-7,7);
      } else {
        last_7 = key;
      }
      ss << std::hex << last_7;
      ss >> step_size;
      ss.ignore(10,'\n');
      ss.clear();
      step_size = step_size % Keys.size(); // end of first double hashing scenario
    }
    else {// if the original hash function is Last7, use XOR'
      if (key.length() > 7) {
        for (size_t i = 0;i<key.length();i++) {
          if (key.length() - i >= 7) {
            substring = key.substr(i,7);
          } else {
            substring = key.substr(i);
          }
          ss << std::hex << substring;
          ss >> dummy;
          ss.ignore(10,'\n');
          ss.clear();
          Substrings.push_back(dummy);
        }
        // if the length of key is not a multiple of 7
        if (key.length() % 7 != 0) {
          substring = key.substr(key.length() - (key.length() % 7),key.length() % 7);
          ss << std::hex << substring;
          ss >> dummy;
          ss.ignore(10,'\n');
          ss.clear();
          Substrings.push_back(dummy);
        }
        for (int value : Substrings) {
          step_size ^= value;
        }
        step_size = step_size % Keys.size();
      }
    }
  }
  if (step_size == 0) {
    step_size = 1;
  }
  // now we have step_size from hashing the key with the other hash, and can use it.
  // we already know that the key collided with something in Keys[index].
  // so we just go through the keys vector and check for the empty spot
  int counter2 = 1;
  do {
    if (Keys[(index + step_size*counter2) % Keys.size()].empty()) {
      Keys[(index + step_size*counter2) % Keys.size()] = key;
      Vals[(index + step_size*counter2) % Keys.size()] = val;
      Nkeys++;
      return "";
    }
    if (Keys[(index + step_size*counter2) % Keys.size()] == key) {
      return "Key already in the table";
    }
    if (Keys[(index + step_size*counter2) % Keys.size()] == Keys[index]) {
      return "Cannot insert key"; // this means that the while loop circled all the way
      // through the vector and returned back to the start. we stop this to prevent an
      // infinite loop.
    }
    counter2++;
  } while (true);
}

std::string Hash_202::Find(const std::string &key) {
  // error check
if (Keys.empty()) {
    return "";
  }
  for (size_t i = 0; i < key.length(); i++) {
    if (key[i] != '0' && key[i] != '1' && key[i] != '2' && key[i] != '3' && key[i] != '4' && key[i] != '5'
      && key[i] != '6' && key[i] != '7' && key[i] != '8' && key[i] != '9' && key[i] !=
      'a' && key[i] != 'b' && key[i] != 'c' && key[i] != 'd' && key[i] != 'e' && key[i] != 'f') {
      return "";
    }
  }
// initialize those variables
  std::stringstream ss;
  std::string substring;
  std::vector<int> Substrings;
  unsigned int index;
  int dummy;
  std::string last_7;
  int step_size;
  // check the vectors depending on the collision resolution strategy
  if (Fxn == 'L') {
    if (key.length() > 7) {
      last_7 = key.substr(key.length()-7,7);
    }
    else {
      last_7 = key;
    }
    ss << std::hex << last_7;
    ss >> index;
    index = index % Keys.size();
  }
  else {
    index = 0;
    if (key.length() > 7) {
      for (size_t i = 0; i < key.length(); i += 7) {
        if (key.length() - i >= 7) {
          substring = key.substr(i, 7);
        } else {
          substring = key.substr(i);
        }
        ss << std::hex << substring;
        ss >> dummy;
        ss.ignore(10,'\n');
        ss.clear();
        Substrings.push_back(dummy);
      }
      for (int value : Substrings) {
        index ^= value;
      }
      index = index % Keys.size();
    } else {
      ss << std::hex << key;
      ss >> index;
      ss.ignore(10,'\n');
      ss.clear();
      index = index % Keys.size();
    }
  }
  // now we have the index, we just have to find the value

  Nprobes = 0;  // Initialize Nprobes to zero for the first probe
  // the easy case, when it's right where we need it
  if (Keys[index] == key) {
    return Vals[index];
  }
  // deal with linear probing first
  if (Coll == 'L') {
    size_t counter = 1;
    while (true) {
      Nprobes++;  // Increment Nprobes for each additional probe
      if (Keys[(index + counter) % Keys.size()].empty()) {
        return "";
      }
      if (Keys[(index + counter) % Keys.size()] == key) {
        return Vals[(index + counter) % Keys.size()];
      }
      counter++;
      if (counter == Keys.size()) return "";
    }
  }
  // if the first hash was XOR
  else {
    if (Fxn == 'X') {
      if (key.length() > 7) {
        last_7 = key.substr(key.length()-7,7);
      } else {
        last_7 = key;
      }
      ss << std::hex << last_7;
      ss >> step_size;
      ss.ignore(10,'\n');
      ss.clear();
      step_size = step_size % Keys.size();
    }
    else {
      if (key.length() > 7) {
        for (size_t i = 0; i < key.length(); i += 7) {
          if (key.length() - i >= 7) {
            substring = key.substr(i,7);
          } else {
            substring = key.substr(i);
          }
          ss << std::hex << substring;
          ss >> dummy;
          ss.ignore(10,'\n');
          ss.clear();
          Substrings.push_back(dummy);
        }
        for (int value : Substrings) {
          step_size ^= value;
        }
        step_size = step_size % Keys.size();
      }
    }
    // avoiding infinite loops
    if (step_size == 0) {
      step_size = 1;
    }
    int counter2 = 1;
    do {
      Nprobes++;  // increment Nprobes for each additional probe
      if (Keys[(index + step_size*counter2) % Keys.size()].empty()) {
        return "";
      }
      if (Keys[(index + step_size*counter2) % Keys.size()] == key) {
        return Vals[(index + step_size*counter2) % Keys.size()];
      }
      if (Keys[(index + step_size*counter2) % Keys.size()] == Keys[index]) {
        return "";
      }
      counter2++;
    } while (true);
  }
}
// print is easy, just go through the vectors and format properly
void Hash_202::Print() const {
  for (size_t i = 0;i<Keys.size();i++) {
    if (Keys[i].empty()) {
      continue;
    }
    std::cout << std::setw(5) << i << " " << Keys[i] << " " << Vals[i] << std::endl;
  }
}
// just call Find on each key
size_t Hash_202::Total_Probes() {
  // easy case
    if (Keys.empty()) return 0;
    
    size_t total_probes = 0;
    for (std::string key : Keys) {
        if (!key.empty()) {
            Find(key);  // this will find Nprobes for this key
            total_probes += Nprobes;
        }
    }
    return total_probes;
}
