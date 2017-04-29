/**
 * sort algorithms
 * created by lisovskey
 */

#ifndef SORT_H
#define SORT_H

#include <utility>
#include <iterator>

using std::prev;
using std::next;
using std::swap;

template <typename BidIt, typename Pred>
void bsort(BidIt first, BidIt last, Pred compare)
/// bubble sort
{
	bool swapped;
	do {
		swapped = false;
		for (BidIt i = next(first); i != last; ++i) {
			if (compare(*i, *prev(i))) {
				swap(*i, *prev(i));
				swapped = true;
			}
		}
	} while (swapped);
}

template <typename BidIt, typename Pred>
void isort(BidIt first, BidIt last, Pred compare)
/// insertion sort
{
	for (BidIt i = next(first); i != last; ++i) {
		for (BidIt j = i; j != first && compare(*j, *prev(j)); --j) {
			swap(*j, *prev(j));
		}
	}
}

template <typename BidIt, typename Pred>
void ssort(BidIt first, BidIt last, Pred compare)
/// selection sort
{
	for (BidIt i = first; i != prev(last); ++i) {
		BidIt tmp = i;
		for (BidIt j = next(i); j != last; ++j) {
			if (compare(*j, *tmp)) {
				tmp = j;
			}
		}
		if (tmp != i) {
			swap(*i, *tmp);
		}
	}
}

template <typename RanIt, typename Pred>
void shsort(RanIt first, RanIt last, Pred compare)
/// shell sort
{
	for (auto d = (last - first) / 2; d > 0; d /= 2) {
		for (RanIt i = first + d; i != last; ++i) {
			for (RanIt j = i; j - first >= d && compare(*j, *(j - d)); j -= d) {
				swap(*j, *(j - d));
			}
		}
	}
}

#endif