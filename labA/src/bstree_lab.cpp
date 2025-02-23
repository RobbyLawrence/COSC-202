#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "bstree.hpp"
using namespace std;
using CS202::BSTree;
using CS202::BSTNode;

int BSTree::Depth(const std::string &key) const {
    BSTNode *current = sentinel->right; // Root node
    int depth = 0;

    while (current != nullptr) {
        if (key == current->key) {
            return depth;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
        depth++;
    }
    return -1; // Key not found
}

int BSTree::Height() const {
    return recursive_find_height(sentinel->right); // Start from the root
}

std::vector<std::string> BSTree::Ordered_Keys() const {
    std::vector<std::string> keys;
    make_key_vector(sentinel->right, keys); // Start from the root
    return keys;
}
   
BSTree::BSTree(const BSTree &t) {
    sentinel = new BSTNode();
    sentinel->left = sentinel->right = sentinel->parent = nullptr;
    size = 0;

    *this = t; // Use assignment operator
}

BSTree& BSTree::operator=(const BSTree &t) {
    if (this == &t) {
        return *this; // Self-assignment check
    }
    Clear(); // Clear current tree

    std::vector<std::string> keys = t.Ordered_Keys();
    std::vector<void*> vals = t.Ordered_Vals();

    size = keys.size();
    sentinel->right = make_balanced_tree(keys, vals, 0, size);
    if (sentinel->right != nullptr) {
        sentinel->right->parent = sentinel;
    }
    return *this;
}

int BSTree::recursive_find_height(const BSTNode *n) const {
    if (n == nullptr) {
        return 0;
    }
    int left_height = recursive_find_height(n->left);
    int right_height = recursive_find_height(n->right);
    return 1 + std::max(left_height, right_height);
}

void BSTree::make_key_vector(const BSTNode *n, std::vector<std::string> &v) const {
    if (n == nullptr) {
        return;
    }
    make_key_vector(n->left, v);
    v.push_back(n->key);
    make_key_vector(n->right, v);
}

BSTNode* BSTree::make_balanced_tree(const std::vector<std::string> &sorted_keys,
                                    const std::vector<void*> &vals,
                                    size_t first_index,
                                    size_t num_indices) const {
    if (num_indices == 0) {
        return nullptr;
    }
    size_t mid = first_index + num_indices / 2;

    BSTNode *node = new BSTNode();
    node->key = sorted_keys[mid];
    node->val = vals[mid];

    node->left = make_balanced_tree(sorted_keys, vals, first_index, mid - first_index);
    if (node->left != nullptr) {
        node->left->parent = node;
    }

    node->right = make_balanced_tree(sorted_keys, vals, mid + 1, (first_index + num_indices) - (mid + 1));
    if (node->right != nullptr) {
        node->right->parent = node;
    }

    return node;
}

