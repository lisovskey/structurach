/**
 * sort algorithms
 * created by lisovskey
 */

#ifndef SORT_H
#define SORT_H

#include <vector>
#include <functional>
#include <iostream>

using std::vector;
using std::swap;
using std::function;

template <typename T>
void bsort(vector<T> &data, function<bool(T, T)> compare) {
    bool swapped;
    do {
        swapped = false;
        for (size_t i = 1; i < data.size(); i++) {
            if (compare(data[i], data[i - 1])) {
                swap(data[i], data[i - 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

template <typename T>
void isort(vector<T> &data, function<bool(T, T)> compare) {
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = i; j > 0 && compare(data[j], data[j - 1]); j--) {
            swap(data[j], data[j - 1]);
        }
    }
}

#endif
