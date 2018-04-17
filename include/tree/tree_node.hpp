/*
 * node of binary search tree
 * created by lisovskey
 */

#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include "tree.hpp"

namespace rzd {

template <
  typename Key,
  typename T,
  typename Compare
> struct tree<Key, T, Compare>::node {

  tree& tree_ref;

  using value_type = typename tree::value_type;
  using pointer = typename tree::pointer;

  value_type data;
  pointer left;
  pointer parent;
  pointer right;

  node(tree& tree_ref, const pointer& parent, const value_type& data)
      : tree_ref{ tree_ref }
      , data{ data }
      , left{ nullptr }
      , parent{ parent }
      , right{ nullptr } {
    tree_ref.size_count++;
  }

  ~node() {
    tree_ref.size_count--;
  }

};

}

#endif