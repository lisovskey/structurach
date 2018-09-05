## Binary Search Tree
Behaves like `std::map` but does not auto-balancing
### Getting Started
#### Include
```
// path must be valid
#include "map.hpp"
```
#### Create map
```
// creates empty map with less-sorting
rzd::map<int, std::string> sample_map;

// adds nodes
rzd::map<int, std::string> sample_map{ { 42, "ritzeed" }, { 24, "rzd" } };

// specifies sort order
rzd::map<int, std::string, std::greater<>> sample_map;
```
#### Add nodes
```
// gives access to value 
sample_map[42] = "ritzeed";

// or by common way
sample_map.insert({ 42, "ritzeed" });
```
#### Find nodes
```
// returns iterator
auto it = sample_map.find(42);

// returns value
auto answer = sample_map[42];

// or by iterating
auto it = sample_map.begin();
```
#### Erase nodes
```
// returns if node was erased
bool success = sample_map.erase(it);

// or by overall clean
sample_map.clear();
```
#### Iterating
```
// insert node and erase next, for example
sample_map.erase(++sample_map.insert({ 42, "ritzeed" }));

// iterate over all map
for (auto& node : sample_map) {
    node.second = "ritzeed";
}
```