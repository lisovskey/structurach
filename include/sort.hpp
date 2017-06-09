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

RZD_BEGIN

// iterator check
template <typename It, typename T>
constexpr bool is = std::is_same<std::iterator_traits<It>::iterator_category, T>::value;

// bubble sort
template <typename BidIt, typename Pred>
void bsort(BidIt first, BidIt last, Pred compare) noexcept
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

// insertion sort
template <typename BidIt, typename Pred>
void isort(BidIt first, BidIt last, Pred compare) noexcept
{
	static_assert(is<BidIt, std::bidirectional_iterator_tag> || is<BidIt, std::random_access_iterator_tag>,
		"bidirectional iterator required");

	for (BidIt i = std::next(first); i != last; ++i) {
		for (BidIt j = i; j != first && compare(*j, *std::prev(j)); --j) {
			std::swap(*j, *std::prev(j));
		}
	}
}

// selection sort
template <typename BidIt, typename Pred>
void ssort(BidIt first, BidIt last, Pred compare) noexcept
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

// gnome sort
template <typename BidIt, typename Pred>
void gsort(BidIt first, BidIt last, Pred compare) noexcept
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

// shell sort
template <typename RanIt, typename Pred>
void shsort(RanIt first, RanIt last, Pred compare) noexcept
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

// quick sort
template <typename RanIt, typename Pred>
void qsort(RanIt first, RanIt last, Pred compare)
{
	static_assert(is<RanIt, std::random_access_iterator_tag>,
		"random access iterator required");

	if (last - first > 1) {
		using content_type = std::iterator_traits<RanIt>::value_type;

		content_type pivot = *first;
		std::vector<content_type> left(last - first);
		std::vector<content_type> right(last - first);
		RanIt left_end = left.begin();
		RanIt right_end = right.begin();

		for (RanIt i = first + 1; i != last; ++i) {
			compare(*i, pivot) ? *left_end++ = *i : *right_end++ = *i;
		}

		qsort(left.begin(), left_end, compare);
		qsort(right.begin(), right_end, compare);

		std::copy(left.begin(), left_end, first);
		*std::next(first, left_end - left.begin()) = pivot;
		std::copy(right.begin(), right_end, std::next(first, left_end - left.begin() + 1));
	}
}

RZD_END

#endif