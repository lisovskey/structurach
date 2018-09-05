/*
 * node of binary search tree
 * created by lisovskey
 */

#ifndef MAP_NODE_HPP
#define MAP_NODE_HPP

#include "map.hpp"

namespace rzd {

template <
  typename Key,
  typename T,
  typename Compare
> struct map<Key, T, Compare>::node {

  map& map_ref;

  using value_type = typename map::value_type;
  using pointer = typename map::pointer;

  value_type data;
  pointer left;
  pointer parent;
  pointer right;

  node(map& map_ref, const pointer& parent, const value_type& data)
      : map_ref{ map_ref }
      , data{ data }
      , left{ nullptr }
      , parent{ parent }
      , right{ nullptr } {
    map_ref.size_count++;
  }

  ~node() {
    map_ref.size_count--;
  }

};

}

#endif