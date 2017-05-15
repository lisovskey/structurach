/**
 * sort algorithms
 * created by lisovskey
 */

#ifndef SORT_H
#define SORT_H

#include <utility>
#include <algorithm>
#include <iterator>

template <typename It, typename T>
constexpr bool is = std::is_same<std::iterator_traits<It>::iterator_category, T>::value;

template <typename BidIt, typename Pred>
void bsort(BidIt first, BidIt last, Pred compare) noexcept
/// bubble sort
{
	static_assert(is<BidIt, std::bidirectional_iterator_tag> || is<BidIt, std::random_access_iterator_tag>,
		"bidirectional iterator required");

	bool swapped;
	do {
		swapped = false;
		for (BidIt i = std::next(first); i != last; ++i) {
			if (compare(*i, *std::prev(i))) {
				std::swap(*i, *std::prev(i));
				swapped = true;
			}
		}
	} while (swapped);
}

template <typename BidIt, typename Pred>
void isort(BidIt first, BidIt last, Pred compare) noexcept
/// insertion sort
{
	static_assert(is<BidIt, std::bidirectional_iterator_tag> || is<BidIt, std::random_access_iterator_tag>,
		"bidirectional iterator required");

	for (BidIt i = std::next(first); i != last; ++i) {
		for (BidIt j = i; j != first && compare(*j, *std::prev(j)); --j) {
			std::swap(*j, *std::prev(j));
		}
	}
}

template <typename BidIt, typename Pred>
void ssort(BidIt first, BidIt last, Pred compare) noexcept
/// selection sort
{
	static_assert(is<BidIt, std::bidirectional_iterator_tag> || is<BidIt, std::random_access_iterator_tag>,
		"bidirectional iterator required");

	for (BidIt i = first; i != std::prev(last); ++i) {
		BidIt tmp = i;
		for (BidIt j = std::next(i); j != last; ++j) {
			if (compare(*j, *tmp)) {
				tmp = j;
			}
		}
		if (tmp != i) {
			std::swap(*i, *tmp);
		}
	}
}

template <typename BidIt, typename Pred>
void gsort(BidIt first, BidIt last, Pred compare) noexcept
/// gnome sort
{
	static_assert(is<BidIt, std::bidirectional_iterator_tag> || is<BidIt, std::random_access_iterator_tag>,
		"bidirectional iterator required");

	BidIt i = first;
	while (i != last) {
		if (i != first && compare(*i, *std::prev(i))) {
			std::swap(*i, *std::prev(i));
			i--;
		}
		else i++;
	}
}

template <typename RanIt, typename Pred>
void shsort(RanIt first, RanIt last, Pred compare) noexcept
/// shell sort
{
	static_assert(is<RanIt, std::random_access_iterator_tag>,
		"random access iterator required");

	for (auto dist = (last - first) / 2; dist > 0; dist /= 2) {
		for (RanIt i = first + dist; i != last; ++i) {
			for (RanIt j = i; j - first >= dist && compare(*j, *(j - dist)); j -= dist) {
				std::swap(*j, *(j - dist));
			}
		}
	}
}

#endif