#include "../include/blockchain/blockchain.hpp"
#include <string>
#include <list>
#include <cassert>

int main() {
  rzd::blockchain<std::string> chain{ "foo" };

  assert(chain.begin()->data == "foo");

  chain.push({ *std::prev(chain.end()), "bar" });

  assert(std::next(chain.begin())->data  == "bar");
  assert(std::size(chain) == 2);
  assert(std::next(chain.begin())->valid(*chain.begin()));
  assert(std::prev(chain.end())->previous_hash == chain.begin()->hash);

  chain.push({ *chain.begin(), "spam" });

  assert(std::size(chain) == 2);

  std::list<rzd::blockchain<std::string>::block> copy;
  copy.push_back(*chain.begin());
  copy.push_back(*std::next(chain.begin()));
  copy.push_back({ *std::prev(copy.end()), "eggs" });
  copy.push_back({ *std::prev(copy.end()), "sause" });

  assert(std::prev(copy.end())->valid(*std::prev(copy.end(), 2)));

  chain.replace(copy.begin(), copy.end());

  assert(std::size(chain) == 4);
  assert(std::prev(chain.end())->data == "sause");

  rzd::blockchain<std::string> chain2{ "toe" };

  assert(chain > chain2);
  assert(chain.last().data == "sause");
}
