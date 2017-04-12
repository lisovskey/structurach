/**
 * sort algorithms
 * created by lisovskey
 */

#ifndef SORT_H
#define SORT_H

#include <vector>
#include <iterator>

using std::prev;
using std::next;
using std::swap;

template <typename It, typename Function>
void bsort(It first, It last, Function compare)
{
    bool swapped;
    do {
        swapped = false;
        for (auto i = next(first); i != last; i++) {
            if (compare(*i, *(prev(i)))) {
                swap(*i, *prev(i));
                swapped = true;
            }
        }
    } while (swapped);
}

template <typename It, typename Function>
void isort(It first, It last, Function compare)
{
	for (auto i = first; i != last; i++) {
        for (auto j = i; j != first && compare(*j, *prev(j)); j--) {
            swap(*j, *prev(j));
        }
    }
}

#endif
