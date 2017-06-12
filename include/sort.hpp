/**
 * sort algorithms
 * created by lisovskey
 */

#ifndef SORT_H
#define SORT_H

#define RZD_BEGIN namespace rzd {
#define RZD_END }

#include <utility>
#include <algorithm>
#include <iterator>
#include <functional>

RZD_BEGIN

// iterator check
template <typename It, typename T>
constexpr bool is = std::is_base_of<T, std::iterator_traits<It>::iterator_category>::value;

// bubble sort
template <typename BidIt, typename Pred = std::less<>>
void bsort(BidIt first, BidIt last, Pred compare = {})
{
	static_assert(is<BidIt, std::bidirectional_iterator_tag>,
		"at least bidirectional iterator required");

	bool swapped;
	do {
		swapped = false;
		for (BidIt i = std::next(first); i != last; ++i) {
			if (compare(*i, *std::prev(i))) {
				std::iter_swap(i, std::prev(i));
				swapped = true;
			}
		}
	} while (swapped);
}

// insertion sort
template <typename BidIt, typename Pred = std::less<>>
void isort(BidIt first, BidIt last, Pred compare = {})
{
	static_assert(is<BidIt, std::bidirectional_iterator_tag>,
		"at least bidirectional iterator required");

	for (BidIt i = std::next(first); i != last; ++i) {
		for (BidIt j = i; j != first && compare(*j, *std::prev(j)); --j) {
			std::iter_swap(j, std::prev(j));
		}
	}
}

// selection sort
template <typename BidIt, typename Pred = std::less<>>
void ssort(BidIt first, BidIt last, Pred compare = {})
{
	static_assert(is<BidIt, std::bidirectional_iterator_tag>,
		"at least bidirectional iterator required");

	for (BidIt i = first; i != std::prev(last); ++i) {
		BidIt tmp = i;
		for (BidIt j = std::next(i); j != last; ++j) {
			if (compare(*j, *tmp)) {
				tmp = j;
			}
		}
		if (tmp != i) {
			std::iter_swap(i, tmp);
		}
	}
}

// gnome sort
template <typename BidIt, typename Pred = std::less<>>
void gsort(BidIt first, BidIt last, Pred compare = {})
{
	static_assert(is<BidIt, std::bidirectional_iterator_tag>,
		"at least bidirectional iterator required");

	BidIt i = first;
	while (i != last) {
		if (i != first && compare(*i, *std::prev(i))) {
			std::iter_swap(i, std::prev(i));
			i--;
		}
		else i++;
	}
}

// shell sort
template <typename RanIt, typename Pred = std::less<>>
void shsort(RanIt first, RanIt last, Pred compare = {})
{
	static_assert(is<RanIt, std::random_access_iterator_tag>,
		"random access iterator required");

	for (auto dist = (last - first) / 2; dist > 0; dist /= 2) {
		for (RanIt i = first + dist; i != last; ++i) {
			for (RanIt j = i; j - first >= dist && compare(*j, *(j - dist)); j -= dist) {
				std::iter_swap(j, j - dist);
			}
		}
	}
}

// quick sort
template <typename ForIt, typename Pred = std::less<>>
void qsort(ForIt first, ForIt last, Pred compare = {})
{
	static_assert(is<ForIt, std::forward_iterator_tag>,
		"at least forward iterator required");

	const auto size = std::distance(first, last);

	if (size > 1) {
		const auto pivot = *first;

		ForIt pre_mid = std::partition(first, last, [&compare, &pivot](const auto &element) {
			return compare(element, pivot);
		});
		ForIt post_mid = std::partition(pre_mid, last, [&compare, &pivot](const auto &element) {
			return !compare(pivot, element);
		});
		
		qsort(first, pre_mid, compare);
		qsort(post_mid, last, compare);
	}
}

RZD_END

#endif