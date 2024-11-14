/* Name: Robby Lawrence
 * NetID: rlawren9
 * Student ID: 000691931
 * Lab: Code Processor
 * Description: server that processes codes and handles users, points, and phone numbers
 * */
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include "code_processor.hpp"
using namespace std;

bool Code_Processor::New_Prize(const string &id, const string &description, int points, int quantity) {
    if (Prizes.find(id) != Prizes.end() || points <= 0 || quantity <= 0) { // error check
        return false;
    }
    Prize *prize = new Prize(); // create new object and load in parameters
    prize->id = id;
    prize->description = description;
    prize->points = points;
    prize->quantity = quantity;
    Prizes[id] = prize;
    return true;
}

bool Code_Processor::New_User(const string &username, const string &realname, int starting_points) {
    if (Names.find(username) != Names.end() || starting_points < 0) { // error check
        return false;
    }
    User *user = new User(); // create new object, load it up
    user->username = username;
    user->realname = realname;
    user->points = starting_points;
    Names[username] = user;
    return true;
}

bool Code_Processor::Delete_User(const string &username) {
    unordered_map<string,User*>::iterator it = Names.find(username);
    if (it == Names.end()) { // error check
        return false;
    }
    User *user = it->second; // we do this to avoid segfaults
    for (const string &pn : user->phone_numbers) { // get rid of all the user's phone numbers
        Phones.erase(pn);
    }
    delete user; // delete the memory
    Names.erase(it);
    return true;
}

bool Code_Processor::Add_Phone(const string &username, const string &phone) {
    unordered_map<string,User*>::iterator Names_it = Names.find(username);
    if (Names_it == Names.end() || Phones.find(phone) != Phones.end()) { // error check
        return false;
    }
    User *user = Names_it->second; // make a copy of the memory address
    user->phone_numbers.insert(phone); //
    Phones[phone] = user; // put user in map
    return true;
}

bool Code_Processor::Remove_Phone(const string &username, const string &phone) {
    unordered_map<string,User*>::iterator Names_it = Names.find(username);
    if (Names_it == Names.end()) { // error check
        return false;
    }
    User *user = Names_it->second; // copy of the memory address
    unordered_map<string,User*>::iterator Phone_it = Phones.find(phone);
    if (Phone_it == Phones.end() || Phone_it->second != user) { // error check again
        return false;
    }
    user->phone_numbers.erase(phone); // finally, we can remove the phone from both places
    Phones.erase(Phone_it);
    return true;
}

string Code_Processor::Show_Phones(const string &username) const {
    unordered_map<string,User*>::const_iterator user_it = Names.find(username);
    if (user_it == Names.end()) { // error check
        return "BAD USER";
    }
    const User *user = user_it->second; // copy memory address
    string result;
    for (const string &pn : user->phone_numbers) { // print phones
        result += pn + "\n";
    }
    return result;
}

int Code_Processor::Enter_Code(const string &username, const string &code) {
    unordered_map<string,User*>::iterator Names_it = Names.find(username);
    if (Names_it == Names.end() || Codes.find(code) != Codes.end()) { // error check
        return -1;
    }
    unsigned int hash_value = 5381; // djb_hash
    for (char c : code) {
      hash_value = ((hash_value << 5) + hash_value + c);
    }
    int points = 0; // initialize points
    if (hash_value % 17 == 0) {
        points = 10;
    } else if (hash_value % 13 == 0) {
        points = 3;
    } else {
        return 0;
    }
    Codes.insert(code); // put the code into the u_map
    Names_it->second->points += points; // increment user's points
    return points;
}

int Code_Processor::Text_Code(const string &phone, const string &code) {
    unordered_map<string,User*>::iterator Phone_it = Phones.find(phone);
    if (Phone_it == Phones.end() || Codes.find(code) != Codes.end()) { // error checking
        return -1;
    }
    User *user = Phone_it->second; // copy memory address
    unsigned int hash_value = 5381; // djb_hash
    for (char c : code) {
      hash_value = ((hash_value << 5) + hash_value + c);
    }
    int points = 0; // initialize points
    if (hash_value % 17 == 0) { // check how many points
        points = 10;
    } else if (hash_value % 13 == 0) {
        points = 3;
    } else {
        return 0;
    }
    Codes.insert(code); // insert code
    user->points += points; // increment points
    return points;
}

bool Code_Processor::Mark_Code_Used(const string &code) {
    if (Codes.find(code) != Codes.end()) { // error checking
        return false;
    }
    unsigned int hash_value = 5381; // djb_hash again
    for (char c : code) {
      hash_value = ((hash_value << 5) + hash_value + c);
    }
    if (hash_value % 17 == 0 || hash_value % 13 == 0) { // ensure code is valid
        Codes.insert(code); // insert code
        return true;
    }
    return false;
}

int Code_Processor::Balance(const string &username) const {
    unordered_map<string,User*>::const_iterator Names_it = Names.find(username);
    if (Names_it == Names.end()) { // error checking
        return -1;
    }
    return Names_it->second->points; // return number of points
}

bool Code_Processor::Redeem_Prize(const string &username, const string &prize_id) {
    unordered_map<string,User*>::iterator Names_it = Names.find(username);
    unordered_map<string,Prize*>::iterator Prize_it = Prizes.find(prize_id);
    if (Names_it == Names.end() || Prize_it == Prizes.end()) { // error checking
        return false;
    }
    User *user = Names_it->second; // copy memory addresses so we don't segfault
    Prize *prize = Prize_it->second;
    if (user->points < prize->points) { // if the user doesn't have enough points
        return false;
    }
    user->points -= prize->points; // decrement points and quantity
    prize->quantity -= 1;
    if (prize->quantity == 0) { // delete prize if quantity is zero
        delete prize;
        Prizes.erase(Prize_it);
    }
    return true;
}

Code_Processor::~Code_Processor() {
  for (pair<string,User*> name_entry : Names) { // we delete each user's memory address
        delete name_entry.second;
    }
    for (pair<string,Prize*> prize_entry : Prizes) { // same for Prizes
        delete prize_entry.second;
    }
}

bool Code_Processor::Write(const string &filename) const {
    ofstream fout(filename); // initialize fstream
    if (!fout.is_open()) { // error check
        return false;
    }
    for (pair<string,Prize*> pair : Prizes) { // output prizes first
        Prize *prize = pair.second; // copy memory address
        fout << "PRIZE     " << prize->id << "     " << prize->points << "      " << prize->quantity << " " << prize->description << "\n";
    }
    for (pair<string,User*> pair : Names) { // output names second
        User *user = pair.second; // copy memory address
        fout << "ADD_USER  " << user->username << "   " << user->points << " " << user->realname << "\n";
        for (string phone : user->phone_numbers) { // then add phones
            fout << "ADD_PHONE " << user->username << " " << phone << "\n";
        }
    }
    for (string code : Codes) { // finally, mark the used codes
        fout << "MARK_USED " << code << "\n";
    }
    fout.close();
    return true;
}
