/*
 * sort algorithms
 * created by lisovskey
 */

#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <iterator>
#include <functional>

namespace rzd {

    // iterator check
    template <typename It, typename T>
    constexpr bool is = std::is_base_of<T, typename std::iterator_traits<It>::iterator_category>::value;

    // bubble sort
    template <typename ForIt, typename Pred = std::less<>>
    void bsort(ForIt first, ForIt last, Pred compare = {})
    {
        static_assert(is<ForIt, std::forward_iterator_tag>,
                      "at least bidirectional iterator required");

        bool swapped;
        do {
            swapped = false;
            for (ForIt i = first; std::next(i) != last; ++i) {
                if (compare(*std::next(i), *i)) {
                    std::iter_swap(std::next(i), i);
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

    // merge sort
    template <typename BidIt, typename Pred = std::less<>>
    void msort(BidIt first, BidIt last, Pred compare = {})
    {
        static_assert(is<BidIt, std::bidirectional_iterator_tag>,
                      "at least forward iterator required");

        const auto size = std::distance(first, last);

        if (size > 1) {
            const auto mid = std::next(first, size / 2);
            msort(first, mid, compare);
            msort(mid, last, compare);
            std::inplace_merge(first, mid, last, compare);
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

    // qsort wrapper
    template <typename It, typename Pred = std::less<>>
    void sort(It first, It last, Pred compare = {})
    {
        rzd::qsort(first, last, compare);            
    }

}

#endif