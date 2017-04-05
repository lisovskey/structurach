#ifndef TREE_TREE_H
#define TREE_TREE_H

#define ANYWAY

#include <iostream>
#include <experimental/optional>

using std::experimental::optional;
using std::experimental::make_optional;

template <typename T>
class Tree
{
    using pair = std::pair<uint, T>;

public:
    // constructors
    Tree() : root(NULL) {}
    Tree(uint key, T value) : root(new node(pair(key, value))) {}

    // destructor
    ~Tree();

    // usable methods
    void insert(uint, T);
    optional<T> find(uint);
    void remove(uint);
    uint size();

private:
    // unit of tree
    struct node {
        pair data;
        node *left;
        node *right;
        node(pair data) : data(data), left(NULL), right(NULL) {}
    } *root;

    // helpers
    void _clear(node*);
    void* _insert(node*, pair);
    void* _find(node*, uint);
    void* _min(node*);
    void* _max(node*);
    void* _remove(node*, uint);
    uint _size(node*);
};

//          CONDITION                           ACTION

template <typename T>
Tree<T>::~Tree()
{
    if      (root)                              _clear(root);
}

template <typename T>
void Tree<T>::_clear(node* leaf)
{
    if      (leaf->left)                        _clear(leaf->left);
    if      (leaf->right)                       _clear(leaf->right);
    ANYWAY                                      delete leaf;
}

template <typename T>
void Tree<T>::insert(uint key, T value)
{
    ANYWAY                                      root = (node*)_insert(root, pair(key, value));
}

template <typename T>
void* Tree<T>::_insert(node* leaf, pair data)
{
    if      (!leaf)                             return leaf = new node(data);
    else if (data.first < leaf->data.first)     leaf->left = (node*)_insert(leaf->left, data);
    else if (data.first > leaf->data.first)     leaf->right = (node*)_insert(leaf->right, data);
    else                                        leaf->data.first = data.first;
    ANYWAY                                      return leaf;
}

template <typename T>
optional<T> Tree<T>::find(uint key)
{
    ANYWAY                                      void* leaf = _find(root, key);
    if      (leaf)                              return make_optional(((node*)leaf)->data.second);
    else                                        return {};
}

template <typename T>
void* Tree<T>::_find(node* leaf, uint key)
{
    if      (!leaf || leaf->data.first == key)  return leaf;
    else if (key < leaf->data.first)            return (node*)_find(leaf->left, key);
    else                                        return (node*)_find(leaf->right, key);
}

template <typename T>
void* Tree<T>::_min(node* leaf)
{
    if      (leaf->left)                        return (node*)_min(leaf->left);
    else                                        return leaf;
}

template <typename T>
void* Tree<T>::_max(node* leaf)
{
    if      (leaf->right)                       return (node*)_min(leaf->right);
    else                                        return leaf;
}

template <typename T>
void Tree<T>::remove(uint key)
{
    ANYWAY                                      root = (node*)_remove(root, key);
}

template <typename T>
void* Tree<T>::_remove(node* leaf, uint key)
{
    if      (!leaf)                             return leaf;
    else if (key < leaf->data.first)            leaf->left = (node*)_remove(leaf->left, key);
    else if (key > leaf->data.first)            leaf->right = (node*)_remove(leaf->right, key);
    else if (leaf->left && leaf->right) {
                                                leaf->data.first = ((node*)_min(leaf->right))->data.first;
                                                leaf->right = (node*)_remove(leaf->right, leaf->data.first);
    }
    else if (leaf->left) {
                                                node* tmp = leaf;
                                                leaf = leaf->left;
                                                delete tmp;
    }
    else if (leaf->right) {
                                                node* tmp = leaf;
                                                leaf = leaf->right;
                                                delete tmp;
    }
    else {
                                                delete leaf;
                                                leaf = NULL;
    }
    ANYWAY                                      return leaf;
}

template <typename T>
uint Tree<T>::size()
{
    ANYWAY                                      return _size(root);
}

template <typename T>
uint Tree<T>::_size(node* leaf)
{
    if      (!leaf)                             return 0;
    else                                        return _size(leaf->left) + 1 + _size(leaf->right);
}

#endif