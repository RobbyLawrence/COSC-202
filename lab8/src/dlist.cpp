/*Name: Robby Lawrence
  NetID: rlawren9
  Student ID: 000691931
  Lab: Dlist
  Description: implementation of class for doubly-linked lists
  */
#include "dlist.hpp"
#include <iostream>
using namespace std;

Dlist::Dlist() {
    sentinel = new Dnode; // create new node
    sentinel->flink = sentinel; // link it to itself
    sentinel->blink = sentinel;
    size = 0;
}

Dlist::Dlist(const Dlist &d) { // same as the first constructor, just add nodes afterwards
    sentinel = new Dnode;
    sentinel->flink = sentinel;
    sentinel->blink = sentinel;
    size = 0;
    for (Dnode *current = d.Begin(); current != d.End(); current = current->Next()) {
        Push_Back(current->s);
    }
}

Dlist& Dlist::operator= (const Dlist &d) {
    if (this != &d) {
        Clear(); // remove all nodes except sentinel
        for (Dnode *node = d.Begin(); node != d.End(); node = node->Next()) {
            Push_Back(node->s); // loop through and copy the nodes
        }
    }
    return *this; // return
}

Dlist::~Dlist() {
    Clear(); // remove all the nodes except the sentinel
    delete sentinel; // then remove the sentinel
}

void Dlist::Clear() {
    Dnode *current = sentinel->flink; // we move forward through the list
    while (current != sentinel) {
        Dnode *temp = current; // assign to prevent segfaults
        current = current->flink; // kind of like incrementing
        delete temp; // delete
    }
    sentinel->flink = sentinel; // we don't delete the sentinel
    sentinel->blink = sentinel;
    size = 0;
}

bool Dlist::Empty() const {
    if (size == 0) {
      return true;
    }
    return false;
}

Dnode* Dnode::Next() {
    return flink; // return next node
}

Dnode* Dnode::Prev() {
    return blink; // return previous node
}

size_t Dlist::Size() const {
    return size; // return size
}

void Dlist::Push_Front(const string &s) {
    Dnode *new_node = new Dnode; // create new node, update all memory addresses
    new_node->s = s;
    new_node->flink = sentinel->flink;
    new_node->blink = sentinel;
    sentinel->flink->blink = new_node;
    sentinel->flink = new_node;
    size++;
}

void Dlist::Push_Back(const string &s) {
    Dnode *new_node = new Dnode; // same as push_front, but from the back
    new_node->s = s;
    new_node->flink = sentinel;
    new_node->blink = sentinel->blink;
    sentinel->blink->flink = new_node;
    sentinel->blink = new_node;
    size++;
}

string Dlist::Pop_Front() {
    if (Empty()) { // error check
        cerr << "list is empty" << endl;
        return "";
    }
    Dnode *f_node = sentinel->flink; // temp
    string f_s = f_node->s; // update memory addresses
    sentinel->flink = f_node->flink;
    f_node->flink->blink = sentinel;
    delete f_node; // delete the node
    size--; // decrement the size
    return f_s;
}

string Dlist::Pop_Back() { // same as pop_front, but from the back
    if (Empty()) { // error check
        cerr << "list is empty" << endl;
        return "";
    }
    Dnode *b_node = sentinel->blink;
    string b_s = b_node->s;
    sentinel->blink = b_node->blink;
    b_node->blink->flink = sentinel;
    delete b_node;
    size--;
    return b_s;
}

Dnode* Dlist::Begin() const { // return first node
    return sentinel->flink;
}

Dnode* Dlist::End() const { // return sentinel node address
    return sentinel;
}

Dnode* Dlist::Rbegin() const { // returns last node
    return sentinel->blink;
}

Dnode* Dlist::Rend() const { // return sentinel
    return sentinel;
}

void Dlist::Insert_Before(const string &s, Dnode *n) {
    if (n == nullptr) {
        return;
    }
    Dnode *newNode = new Dnode;
    newNode->s = s;
    newNode->flink = n;
    newNode->blink = n->blink;
    n->blink->flink = newNode;
    n->blink = newNode;
    size++;
}

void Dlist::Insert_After(const string &s, Dnode *n) {
    if (n == nullptr) { // error check
        return;
    }
    Dnode *new_node = new Dnode; // create new object
    new_node->s = s; // update addresses
    new_node->blink = n;
    new_node->flink = n->flink;
    n->flink->blink = new_node;
    n->flink = new_node;
    size++; // increment size
}

void Dlist::Erase(Dnode *n) {
    if (n == nullptr || n == sentinel) { // error check
        return;
    }
    n->blink->flink = n->flink; // update addresses
    n->flink->blink = n->blink;
    delete n;
    size--; // decrement size
}
