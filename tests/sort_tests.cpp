#include "../include/sort/sort.hpp"
#include <cassert>
#include <iterator>
#include <forward_list>
#include <list>
#include <vector>

template <typename List>
bool test(List list, void(*some_sort)(typename List::iterator,
                                      typename List::iterator,
                                      bool(*)(int, int))) {
	some_sort(list.begin(), list.end(), [](int a, int b) { return a < b; });

	if (std::distance(list.begin(), list.end()) > 1) {
		for (auto i = list.begin(); std::next(i) != list.end(); ++i) {
			if (*i > *std::next(i)) {
				return false;
			}
		}
	}

	return true;
}

int main() {
	std::initializer_list<int> init_list{ 5, -3, 0, 1, 3, -2, 2, 4, -5, -4, -1 };

	std::forward_list<int> for_list{ init_list };
	std::list<int> bid_list{ init_list };
	std::vector<int> ran_list{ init_list };

	assert(test(for_list, rzd::bubble_sort));
	assert(test(for_list, rzd::quick_sort));

	assert(test(bid_list, rzd::selection_sort));
	assert(test(bid_list, rzd::insertion_sort));
	assert(test(bid_list, rzd::gnome_sort));
	assert(test(bid_list, rzd::merge_sort));	

	assert(test(ran_list, rzd::shell_sort));
}