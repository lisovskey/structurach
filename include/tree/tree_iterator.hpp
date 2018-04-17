/*
 * iterator of binary search tree
 * created by lisovskey
 */

#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "tree.hpp"
#include <stdexcept>

namespace rzd {

template <
  typename Key,
  typename T,
  typename Compare
> class tree<Key, T, Compare>::iterator {

  using pointer = typename tree::pointer;
  using value_type = typename tree::value_type;

  const tree& tree_ref;
  bool is_end;

  pointer prev_parent(pointer leaf) {
    if (leaf->parent == nullptr)
      throw std::out_of_range("iterator went over the begin");
    else if (tree_ref.cmp(leaf->parent->data.first, leaf->data.first))				
      return leaf->parent;
    else
      return prev_parent(leaf->parent);
  }

  pointer next_parent(pointer leaf) {
    if (leaf->parent == nullptr)
      return nullptr;
    else if (tree_ref.cmp(leaf->data.first, leaf->parent->data.first))
      return leaf->parent;
    else
      return next_parent(leaf->parent);
  }

public:

  pointer node_ptr;

  iterator& operator--() {
    if (is_end)
      node_ptr = tree_ref.rightmost(tree_ref.root);
    else if (node_ptr == nullptr)
      throw std::out_of_range("iterator went wrong way");
    else if (node_ptr->left != nullptr)
      node_ptr = tree_ref.rightmost(node_ptr->left);
    else
      node_ptr = prev_parent(node_ptr);
    is_end = false;
    return *this;
  }

  iterator& operator++() {
    if (is_end)
      throw std::out_of_range("iterator went over the end");
    else if (node_ptr == nullptr)
      throw std::out_of_range("iterator went wrong way");
    else if (node_ptr->right != nullptr)
      node_ptr = tree_ref.leftmost(node_ptr->right);
    else if (!(node_ptr = next_parent(node_ptr)))
      is_end = true;
    return *this;
  }

  iterator operator--(int) {
    iterator result{ *this };
    --(*this);
    return result;
  }

  iterator operator++(int) {
    iterator result{ *this };
    ++(*this);
    return result;
  }

  value_type& operator*() {
    return node_ptr->data;
  }

  value_type* operator->() {
    return &node_ptr->data;
  }

  bool operator==(const iterator& it) {
    return node_ptr == it.node_ptr;
  }

  bool operator!=(const iterator& it) {
    return node_ptr != it.node_ptr;
  }

  iterator(const tree& tree_ref, pointer leaf)
      : tree_ref{ tree_ref }
      , node_ptr{ leaf } {
    is_end = (node_ptr == nullptr);
  }

};

}

#endif