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
rzd::merge_sort(sample_list.begin(), sample_list.end());
```
### Avalible sort algorithms:
 * `rzd::bubble_sort`
 * `rzd::insertion_sort`
 * `rzd::selection_sort`
 * `rzd::gnome_sort`
 * `rzd::shell_sort`
 * `rzd::merge_sort`
 * `rzd::quick_sort`