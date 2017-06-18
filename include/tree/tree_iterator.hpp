/*
 * iterator of binary search tree
 * created by lisovskey
 */

#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "tree.hpp"

namespace rzd {

	template <
		typename Key,
		typename T,
		typename Compare
	> class tree<Key, T, Compare>::iterator {

		using pointer = typename tree::pointer;
		using reference = typename tree::reference;

		const tree& tree_ref;
		bool is_end;

		pointer prev_parent(pointer leaf)
		{
			if (!leaf->parent)
				throw std::exception();
			else if (tree_ref.cmp(leaf->parent->data.first, leaf->data.first)) {
				is_end = false;
				return leaf->parent;
			}
			else
				return prev_parent(leaf->parent);
		}

		pointer next_parent(pointer leaf)
		{
			if (!leaf->parent)
				return nullptr;
			else if (tree_ref.cmp(leaf->data.first, leaf->parent->data.first))
				return leaf->parent;
			else
				return next_parent(leaf->parent);
		}

	public:

		pointer leaf;

		iterator& operator--()
		{
			if (is_end)
				leaf = tree_ref.rightmost();
			else if (value->left)
				leaf = tree_ref.rightmost(leaf->left);
			else
				leaf = prev_parent(value);
			return *this;
		}

		iterator& operator++()
		{
			if (is_end)
				throw std::exception();
			else if (leaf->right)
				leaf = tree_ref.leftmost(leaf->right);
			else if (!(leaf = next_parent(leaf)))
				is_end = true;
			return *this;
		}

		iterator operator--(int)
		{
			iterator result{ *this };
			--(*this);
			return result;
		}

		iterator operator++(int)
		{
			iterator result{ *this };
			++(*this);
			return result;
		}

		reference operator*()
		{
			return leaf->data;
		}

		bool operator==(const iterator& it)
		{
			return leaf == it.leaf;
		}

		bool operator!=(const iterator& it)
		{
			return leaf != it.leaf;
		}

		iterator(const tree& tree_ref, pointer leaf, bool is_end)
			: tree_ref{ tree_ref }
			, leaf{ leaf }
			, is_end{ is_end } {}

	};

}

#endif