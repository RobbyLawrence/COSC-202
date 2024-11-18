#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "bstree.hpp"
using namespace std;
using CS202::BSTree;
using CS202::BSTNode;

/* ---------------------------------------------- */
/* You'll write all of these as part of your lab. */

BSTree::BSTree()
{
  sentinel = new BSTNode;
  sentinel->left = NULL;
  sentinel->right = sentinel;
  sentinel->parent = NULL;
  sentinel->key = "---SENTINEL---";
  sentinel->val = NULL;
  size = 0;
}


bool BSTree::Insert(const string &key, void *val)
{
  BSTNode *parent;
  BSTNode *n;

  parent = sentinel;
  n = sentinel->right;

  /* Find where the key should go.  If you find the key, return false. */

  while (n != sentinel) {
    if (n->key == key) return false;
    parent = n;
    n = (key < n->key) ? n->left : n->right;
  }

  /* At this point, parent is the node that will be the parent of the new node.
     Create the new node, and hook it in. */

  n = new BSTNode;
  n->key = key;
  n->val = val;
  n->parent = parent;
  n->left = sentinel;
  n->right = sentinel;

  /* Use the correct pointer in the parent to point to the new node. */

  if (parent == sentinel) {
    sentinel->right = n;
  } else if (key < parent->key) {
    parent->left = n;
  } else {
    parent->right = n;
  }

  /* Increment the size and return success. */

  size++;
  return true;
}

void *BSTree::Find(const string &key) const
{
  BSTNode *n;

  n = sentinel->right;
  while (1) {
    if (n == sentinel) return NULL;
    if (key == n->key) return n->val;
    n = (key < n->key) ? n->left : n->right;
  }
}

bool BSTree::Delete(const string &key)
{
  BSTNode *n, *parent, *mlc;
  string tmpkey;
  void *tmpval;

  /* Try to find the key -- if you can't return false. */

  n = sentinel->right;
  while (n != sentinel && key != n->key) {
    n = (key < n->key) ? n->left : n->right;
  }
  if (n == sentinel) return false;

  /* We go through the three cases for deletion, although it's a little
     different from the canonical explanation. */

  parent = n->parent;

  /* Case 1 - I have no left child.  Replace me with my right child.
     Note that this handles the case of having no children, too. */

  if (n->left == sentinel) {
    if (n == parent->left) {
      parent->left = n->right;
    } else {
      parent->right = n->right;
    }
    if (n->right != sentinel) n->right->parent = parent;
    delete n;
    size--;

  /* Case 2 - I have no right child.  Replace me with my left child. */

  } else if (n->right == sentinel) {
    if (n == parent->left) {
      parent->left = n->left;
    } else {
      parent->right = n->left;
    }
    n->left->parent = parent;
    delete n;
    size--;

  /* If I have two children, then find the node "before" me in the tree.
     That node will have no right child, so I can recursively delete it.
     When I'm done, I'll replace the key and val of n with the key and
     val of the deleted node.  You'll note that the recursive call 
     updates the size, so you don't have to do it here. */

  } else {
    for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
    tmpkey = mlc->key;
    tmpval = mlc->val;
    Delete(tmpkey);
    n->key = tmpkey;
    n->val = tmpval;
  }

  return true;
}

size_t BSTree::Size() const
{
  return size;
}

bool BSTree::Empty() const
{
  return (size == 0);
}

void BSTree::Print() const
{
  recursive_inorder_print(0, sentinel->right);
}

void BSTree::recursive_inorder_print(int level, const BSTNode *n) const
{
  if (n == sentinel) return;
  recursive_inorder_print(level+2, n->right);
  printf("%*s%s\n", level, "", n->key.c_str());
  recursive_inorder_print(level+2, n->left);
}

vector <void *> BSTree::Ordered_Vals() const
{
  vector <void *> rv;
  make_val_vector(sentinel->right, rv);
  return rv;
}

void BSTree::make_val_vector(const BSTNode *n, vector<void *> &v) const
{
  if (n == sentinel) return;
  make_val_vector(n->left, v);
  v.push_back(n->val);
  make_val_vector(n->right, v);
}

void BSTree::Clear()
{
  recursive_destroy(sentinel->right);
  sentinel->right = sentinel;
  size = 0;
}

void BSTree::recursive_destroy(BSTNode *n)
{
  if (n == sentinel) return;
  recursive_destroy(n->left);
  recursive_destroy(n->right);
  delete n;
}

BSTree::~BSTree()
{
  Clear();
  delete sentinel;
}

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

