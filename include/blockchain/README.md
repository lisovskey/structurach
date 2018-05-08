## Blockchain
It is minimal interface for doing a barrel roll
### Getting Started
#### Include
```
// path must be valid
#include "blockchain.hpp"
```
#### Create blockchain
```
// creates chain of one genesis block that stores a string
rzd::blockchain<std::string> chain{ "genesis" };
```
#### Add blocks
```
// construct a block on the fly
chain.push({ chain.last(), "such transactions" });
```
#### Replace chain
```
// replaces chain if it longer and genesis blocks are the same
chain.replace(another_chain.begin(), another_chain.end());
```
#### Iterating
```
// iterate over all chain
for (auto& block : chain) {
    block.data = "invalid";
}
```
