#include "../include/tree/tree.hpp"
#include <cassert>
#include <iterator>

int main()
{
    rzd::tree<int, char> tree{ { 0, 'a' }, { 2, 'b' }, { -2, 'c' } };
    tree[-1] = 'd';
    tree[-3] = 'e';
    tree[3] = 'f';

    assert((*tree.insert({ 1, 'g' })).second == 'g');
    assert(tree.erase(0) == true);
    assert(tree.erase(0) == false);
    assert((*tree.begin()).second == 'e');
    assert((*--tree.end()).second == 'f');
    assert((*tree.find(2)).second == 'b');
    assert(std::size(tree) == 6);
    assert(tree.erase(tree.find(-1)) == true);
    assert(tree.empty() == false);

    tree.clear();

    assert(tree.find(3) == tree.end());
    assert(tree.erase(1) == false);
    assert(tree.empty() == true);
    assert(tree.begin() == tree.end());
}