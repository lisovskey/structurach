## Sort Algorithms
Behave like `std::sort` and give freedom of choice
### Getting Started
#### Include
```
// path must be valid
#include "sort.hpp"
```
#### Create container
```
// any container with iterators support can be sorted 
std::list<int> sample_list{ 5, 8, 0, 1, 4, 2, 9, 3, 6, 7 };
```
#### Sort it out
```
// least-to-greatest quick sort is used by default
rzd::sort(sample_list.begin(), sample_list.end());
```
#### Change sort order
```
// lambdas or any std::less-like functions can be passed as well
rzd::sort(sample_list.begin(), sample_list.end(), std::greater<>());
```
#### Specify sort method
```
// merge sort, for example
rzd::msort(sample_list.begin(), sample_list.end());
```
### Avalible sort algorithms:
 * Bubble Sort: `rzd::bsort`
 * Insertion Sort: `rzd::isort`
 * Selection Sort: `rzd::ssort`
 * Gnome Sort: `rzd::gsort`
 * Shell Sort: `rzd::shsort`
 * Merge Sort: `rzd::msort`
 * Quick Sort: `rzd::qsort`