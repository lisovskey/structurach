/*
 * blockchain of blocks
 * created by lisovskey
 */

#include "blockchain_block.hpp"

#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <string>
#include <list>
#include <type_traits>

namespace rzd {

template <
  typename T,
  typename Hash = std::hash<std::string>
> class blockchain {

 public:

  struct block;

  using hash_type = std::invoke_result_t<Hash, std::string>;
  using value_type = block;
  using data_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = block*;
  using iterator = typename std::list<block>::iterator;
  using const_iterator = typename std::list<block>::const_iterator;

 private:

  std::list<block> chain;

  template <typename It>
  difference_type valid_offset(It first, It last) {
    if (*first != *begin() || first == last) {
      return {};
    }
    iterator pos{ std::next(begin()) };
    difference_type index{ 1 };
    for (auto it{ std::next(first) }; it != last; ++it) {
      if (it->valid(*std::prev(it))) {
        if (*pos == *it) {
          ++pos;
          ++index;
        }
      } else {
        return {};
      }
    }
    return index;
  }

 public:

  template <typename It>
  iterator replace(It first, It last) {
    if (auto index{ valid_offset(first, last) },
        range{ std::distance(first, last) };
        index != 0 && range > size()) {
      chain.resize(range);
      return std::copy(std::next(first, index), last,
                       std::next(begin(), index));
    }
    return begin();
  }

  inline void push(const value_type& node) {
    if (node.valid(*std::prev(end())))
      chain.push_back({ node });
  }

  inline iterator begin() {
    return std::begin(chain);
  }

  inline const_iterator cbegin() const {
    return std::cbegin(chain);
  }

  inline iterator end() {
    return std::end(chain);
  }

  inline const_iterator cend() const {
    return std::cend(chain);
  }

  inline size_type size() const {
    return std::size(chain);
  }

  inline block& last() {
    return chain.back();
  }

  inline bool operator<(const blockchain& another) {
    return std::size(chain) < std::size(another);
  }

  inline bool operator>(const blockchain& another) {
    return std::size(chain) > std::size(another);
  }

  explicit blockchain(const data_type& data)
      : chain{ { { {}, data, {} } } } {}

};

}

#endif