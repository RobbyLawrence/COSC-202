#include <ios>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

int main() {
    std::string substring;
    std::stringstream ss;
    std::vector<int> Substrings;
    std::string hexStr = "a000000a00000101";
    int hash = 0;
    int dummy;
    for (int i = 0;i<((hexStr.length() / 7));i++) {
        substring = hexStr.substr(0 + 7*i,7);
        ss << std::hex << substring;
        ss >> dummy;
        ss.ignore(10,'\n');
        ss.clear();
        Substrings.push_back(dummy);
        }

    if (hexStr.length() % 7 != 0) {
        substring = hexStr.substr(hexStr.length() - (hexStr.length() % 7),hexStr.length() % 7);
        ss << std::hex << substring;
        ss >> dummy;
        ss.ignore(10,'\n');
        ss.clear();
        Substrings.push_back(dummy);
    }

    for (int value : Substrings) {
        std::cout << value << std::endl;
        hash ^= value;  
    }
    std::cout << hash << std::endl;
    return 0;
}
