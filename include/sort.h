/**
 * sort algorithms
 * created by lisovskey
 */

#ifndef SORT_H
#define SORT_H

using std::swap;

template <typename Iterator, typename Function>
void bsort(Iterator first, Iterator last, Function compare)
/// bubble sort
{
    bool swapped;
    do {
        swapped = false;
        for (Iterator i = first + 1; i != last; ++i) {
            if (compare(*i, *(i - 1))) {
                swap(*i, *(i - 1));
                swapped = true;
            }
        }
    } while (swapped);
}

template <typename Iterator, typename Function>
void isort(Iterator first, Iterator last, Function compare)
/// insertion sort
{
	for (Iterator i = first + 1; i != last; ++i) {
		for (Iterator j = i; j != first && compare(*j, *(j - 1)); --j) {
            swap(*j, *(j - 1));
        }
    }
}

template <typename Iterator, typename Function>
void shsort(Iterator first, Iterator last, Function compare)
/// shell sort
{
	for (auto d = (last - first) / 2; d > 0; d /= 2) {
		for (Iterator i = first + d; i != last; ++i) {
			for (Iterator j = i; j - first >= d && compare(*j, *(j - d)); j -= d) {
				swap(*j, *(j - d));
			}
		}
	}
}

#endif