/*
 * binary search tree class
 * created by lisovskey
 */

#include "tree_node.hpp"
#include "tree_iterator.hpp"

#ifndef TREE_HPP
#define TREE_HPP

#include <memory>
#include <functional>

namespace rzd {

// binary search tree
template <
  typename Key,
  typename T,
  typename Compare = std::less<Key>
> class tree {

  // unit of tree
  struct node;

 public:

  // in-class types
  using pointer = std::shared_ptr<node>;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<Key, T>;
  using size_type = std::size_t;
  using key_compare = Compare;
  using difference_type = std::ptrdiff_t;

  // bidirectional
  class iterator;

 private:

  // predicate
  key_compare cmp;

  // start point
  pointer root;

  // fast access size
  size_type size_count;

  pointer& insert(pointer& leaf, const value_type& data) {
    if (cmp(data.first, leaf->data.first)) {
      if (leaf->left == nullptr)
        return leaf->left = pointer{ new node{ *this, leaf, data } };
      else
        return insert(leaf->left, data);
    }
    else if (cmp(leaf->data.first, data.first)) {
      if (leaf->right == nullptr)
        return leaf->right = pointer{ new node{ *this, leaf, data } };
      else
        return insert(leaf->right, data);
    } else {
      leaf->data = data;
      return leaf;
    }
  }

  const pointer& find(const pointer& leaf, const key_type& key) const {
    if (leaf == nullptr || leaf->data.first == key) {
      return leaf;
    } else if (cmp(key, leaf->data.first)) {
      return find(leaf->left, key);
    } else {
      return find(leaf->right, key);
    }
  }

  pointer& leftmost(pointer& leaf) {
    if (leaf->left != nullptr) {
      return leftmost(leaf->left);
    } else {
      return leaf;
    }
  }

  const pointer& leftmost(const pointer& leaf) const {
    if (leaf->left != nullptr) {
      return leftmost(leaf->left);
    } else {
      return leaf;
    }
  }

  pointer& rightmost(pointer& leaf) {
    if (leaf->right != nullptr) {
      return rightmost(leaf->right);
    } else {
      return leaf;
    }
  }

  const pointer& rightmost(const pointer& leaf) const {
    if (leaf->right != nullptr) {
      return rightmost(leaf->right);
    } else {
      return leaf;
    }
  }

  bool erase(pointer& leaf, const key_type& key) {
    if (leaf == nullptr) {
      return false;
    } else if (cmp(key, leaf->data.first)) {
      return erase(leaf->left, key);
    } else if (cmp(leaf->data.first, key)) {
      return erase(leaf->right, key);
    } else if (leaf->left != nullptr && leaf->right != nullptr) {
      leaf->data = leftmost(leaf->right)->data;
      return erase(leftmost(leaf->right), leaf->data.first);
    } else if (leaf->left != nullptr) {
      leaf->left->parent = leaf->parent;
      leaf = leaf->left;
    } else if (leaf->right != nullptr) {
      leaf->right->parent = leaf->parent;
      leaf = leaf->right;
    } else {
      leaf = nullptr;
    }
    return true;
  }

  void clear(pointer& leaf) {
    if (leaf != nullptr) {
      clear(leaf->left);
      clear(leaf->right);
      leaf = nullptr;
    }
  }

 public:

  // insert new node with key and value with hint
  inline iterator insert(const iterator& it, const value_type& data) {
    if (it == end())
      return { *this, it = pointer{ new node{ *this, nullptr, data } } };
    else
      return { *this, insert(it.node_ptr, data) };
  }

  // insert new node with key and value
  inline iterator insert(const value_type& data) {
    if (root == nullptr)
      return { *this, root = pointer{ new node{ *this, nullptr, data } } };
    else
      return { *this, insert(root, data) };
  }

  // return iterator by key
  inline iterator find(const key_type& key) {
    if (pointer leaf{ find(root, key) })
      return { *this, leaf };
    else
      return end();
  }

  // return const iterator by key
  inline const iterator find(const key_type& key) const {
    if (pointer leaf{ find(root, key) })
      return { *this, leaf };
    else
      return end();
  }

  // remove node by iterator
  inline bool erase(iterator it) {
    return erase(it.node_ptr, it->first);
  }

  // remove node by key
  inline bool erase(const key_type& key) {
    return erase(root, key);
  }

  // remove all nodes
  inline void clear() {
    clear(root);
  }

  // return number of nodes
  inline size_type size() const {
    return size_count;
  }

  // return true if tree is empty
  inline bool empty() const {
    return size_count == 0;
  }

  // return iterator of the first node
  inline iterator begin() {
    if (root == nullptr)
      return end();
    else
      return { *this, leftmost(root) };
  }

  // return const iterator of the first node
  inline const iterator begin() const {
    if (root == nullptr)
      return end();
    else
      return { *this, leftmost(root) };
  }

  // return iterator of the post-last node
  inline iterator end() {
    return { *this, nullptr };
  }

  // return const iterator of the post-last node
  inline const iterator end() const {
    return { *this, nullptr };
  }

  // return value reference by key
  inline mapped_type& operator[](const key_type& key) {
    if (pointer leaf{ find(root, key) })
      return leaf->data.second;
    else
      return insert(std::make_pair(key, mapped_type{}))->second;
  }

  // create empty tree
  tree()
      : root{ nullptr }
      , cmp{ key_compare{} }
      , size_count{} {}

  // create filled tree
  tree(std::initializer_list<value_type> init)
      : cmp{ key_compare{} }
      , size_count{} {
    for (const value_type& item : init)
      insert(item);
  }

};

}

#endif