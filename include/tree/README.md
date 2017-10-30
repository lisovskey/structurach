## Binary Search Tree
Behaves like `std::map` but does not auto-balancing and has unique keys
### Getting Started
#### Include
```
// path must be valid
#include "tree.hpp"
```
#### Create tree
```
// creates empty tree with less-sorting
rzd::tree<int, std::string> sample_tree;

// adds nodes
rzd::tree<int, std::string> sample_tree{ { 42, "ritzeed" }, { 24, "rzd" } };

// specifies sort order
rzd::tree<int, std::string> sample_tree(std::greater<>());
```
#### Add nodes
```
// gives access to value 
sample_tree[42] = "ritzeed";

// or by common way
sample_tree.insert({ 42, "ritzeed" });
```
#### Find nodes
```
// returns iterator
auto it = sample_tree.find(42);

// returns value
auto answer = sample_tree[42];

// or by iterating
auto it = sample_tree.begin();
```
#### Erase nodes
```
// returns if node was erased
bool success = sample_tree.erase(it);

// or by overall clean
sample_tree.clear();
```
#### Iterating
```
// insert node and erase next, for example
sample_tree.erase(++sample_tree.insert({ 42, "ritzeed" }));

// iterate over all tree
for (auto& node : sample_tree) {
    node.second = "ritzeed";
}
```