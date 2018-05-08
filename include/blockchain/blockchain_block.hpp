/*
 * block of blockchain
 * created by lisovskey
 */

#ifndef BLOCKCHAIN_BLOCK_HPP
#define BLOCKCHAIN_BLOCK_HPP

#include "blockchain.hpp"
#include <sstream>
#include <chrono>

namespace rzd {

template <
  typename T,
  typename Hash
> struct blockchain<T, Hash>::block {

  using hash_type = typename blockchain::hash_type;
  using data_type = typename blockchain::data_type;
  using index_type = typename blockchain::size_type;
  using hasher = Hash;
  using time_type = std::chrono::time_point<std::chrono::system_clock>;
  using clock = std::chrono::system_clock;

  hasher hash_string;
  index_type index;
  data_type data;
  hash_type previous_hash;
  hash_type hash;
  time_type timestamp;

  hash_type get_hash() const {
    std::stringstream ss;
    ss << index
       << data
       << previous_hash
       << clock::to_time_t(timestamp);
    return hash_string(ss.str());
  }

  bool valid(const block& previous_block) const {
    if (index != previous_block.index + 1 ||
        previous_hash != previous_block.hash ||
        hash != get_hash()) {
      return false;
    }
    return true;
  }

  bool operator==(const block& node) {
    return hash == node.hash;
  }

  bool operator!=(const block& node) {
    return hash != node.hash;
  }

  block(const index_type index,
        const data_type& data,
        const hash_type& previous_hash)
      : index{ index }
      , data{ data }
      , previous_hash{ previous_hash } {
    timestamp = clock::now();
    hash = get_hash();
  }

  block(block& previous_block, const data_type& data)
      : block(previous_block.index + 1,
              data,
              previous_block.hash) {}
  
  block(const block& block) = default;
  
  block() = default;

};

}

#endif