/**
 * binary search tree class
 * created by lisovskey
 */

#ifndef TREE_H
#define TREE_H

#define ANYWAY
#define THEN

#include <memory>
#include <experimental/optional>

// waiting for cpp17
using std::experimental::optional;
using std::experimental::make_optional;

template <typename T>
class Tree
{
    // prototype
    struct node;

    // aliases
    using pointer = std::shared_ptr<node>;
    using pair = std::pair<int, T>;

    // unit of tree
    struct node {
        pair data;
        pointer left;
        pointer right;
        node(pair data) : data(data), left(NULL), right(NULL) {}
    };

    // start point
    pointer root;

//              CONDITION                           ACTION

    pointer _insert(pointer leaf, pair data)
    {
        if      (!leaf)                             return leaf = pointer(new node(data));
        else if (data.first < leaf->data.first)     leaf->left = (pointer)_insert(leaf->left, data);
        else if (data.first > leaf->data.first)     leaf->right = (pointer)_insert(leaf->right, data);
        else                                        leaf->data.first = data.first;
        ANYWAY                                      return leaf;
    }

    pointer _find(pointer leaf, int key)
    {
        if      (!leaf || leaf->data.first == key)  return leaf;
        else if (key < leaf->data.first)            return (pointer)_find(leaf->left, key);
        else                                        return (pointer)_find(leaf->right, key);
    }

    pointer _min(pointer leaf)
    {
        if      (leaf->left)                        return (pointer)_min(leaf->left);
        else                                        return leaf;
    }

    pointer _remove(pointer leaf, int key)
    {
        if      (!leaf)                             return leaf;
        else if (key < leaf->data.first)            leaf->left = (pointer)_remove(leaf->left, key);
        else if (key > leaf->data.first)            leaf->right = (pointer)_remove(leaf->right, key);
        else if (leaf->left && leaf->right) {
            THEN                                    leaf->data.first = ((pointer)_min(leaf->right))->data.first;
            THEN                                    leaf->right = (pointer)_remove(leaf->right, leaf->data.first);
        }
        else if (leaf->left)                        leaf = leaf->left;
        else if (leaf->right)                       leaf = leaf->right;
        else                                        leaf = NULL;
        ANYWAY                                      return leaf;
    }

    int _size(pointer leaf)
    {
        if      (!leaf)                             return 0;
        else                                        return _size(leaf->left) + 1 + _size(leaf->right);
    }

public:

    // constructors

    Tree() : root(NULL) {}

    Tree(int key, T value) : root(new node(pair(key, value))) {}

    // usable methods

    void insert(int key, T value)
    {
        ANYWAY                                      root = (pointer)_insert(root, pair(key, value));
    }

    optional<T> find(int key)
    {
        ANYWAY                                      pointer leaf = _find(root, key);
        if      (leaf)                              return make_optional(((pointer)leaf)->data.second);
        else                                        return {};
    }

    void remove(int key)
    {
        ANYWAY                                      root = (pointer)_remove(root, key);
    }

    int size()
    {
        ANYWAY                                      return _size(root);
    }

};

#endif
