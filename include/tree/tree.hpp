/*
 * binary search tree class
 * created by lisovskey
 */

#include "tree_node.hpp"
#include "tree_iterator.hpp"

#ifndef TREE_HPP
#define TREE_HPP

#define RZD_BEGIN namespace rzd {
#define RZD_END }
#define ANYWAY
#define THEN

#include <memory>
#include <optional>
#include <functional>

RZD_BEGIN

// binary search tree
template <
	typename Key,
	typename T,
	typename Compare = std::less<Key>
> class tree {

	// unit of tree
	struct node;

public:

	// in-class types
	using pointer = std::shared_ptr<node>;
	using key_type = Key;
	using mapped_type = T;
	using value_type = std::pair<Key, T>;
	using size_type = std::size_t;
	using key_compare = Compare;
	using mapped_reference = T&;
	using reference = value_type&;
	using difference_type = std::ptrdiff_t;

	// bidirectional
	class iterator;

private:

	// predicate
	key_compare cmp;

	// start point
	pointer root;
	
	// fast access size
	size_type size_count;

	//	IF      CONDITION                           ACTION

	pointer& insert(pointer& leaf, const reference data)
	{
		if      (!leaf)                             leaf = pointer{ new node{ *this, data } };
		else if (cmp(data.first, leaf->data.first)) return insert(leaf->left, data)->parent = leaf;
		else if (cmp(leaf->data.first, data.first)) return insert(leaf->right, data)->parent = leaf;
		else                                        leaf->data.second = data.second;
		ANYWAY                                      return leaf;
	}

	const pointer& find(const pointer& leaf, const key_type& key) const
	{
		if      (!leaf || leaf->data.first == key)  return leaf;
		else if (cmp(key, leaf->data.first))        return find(leaf->left, key);
		else                                        return find(leaf->right, key);
	}

	pointer& leftmost(pointer& leaf) const
	{
		if      (leaf->left)                        return leftmost(leaf->left);
		else                                        return leaf;
	}

	pointer& rightmost(pointer& leaf) const
	{
		if      (leaf->right)                       return rightmost(leaf->right);
		else                                        return leaf;
	}

	bool erase(pointer& leaf, const key_type& key)
	{
		if      (!leaf)                             return false;
		else if (cmp(key, leaf->data.first))        return erase(leaf->left, key);
		else if (cmp(leaf->data.first, key))        return erase(leaf->right, key);
		else if (leaf->left && leaf->right) {
		    THEN                                    leaf->data = leftmost(leaf->right)->data;
		    THEN                                    return erase(leftmost(leaf->right), leaf->data.first);
		}
		else if (leaf->left) {
			THEN                                    leaf->left->parent = leaf->parent;
			THEN                                    leaf = leaf->left;
		}
		else if (leaf->right) {
		    THEN                                    leaf->right->parent = leaf->parent;
		    THEN                                    leaf = leaf->right;
		}
		else                                        leaf = nullptr;
		ANYWAY                                      return true;
	}

	void clear(pointer& leaf)
	{
		if      (leaf) {
		    THEN                                    clear(leaf->left);
		    THEN                                    clear(leaf->right);
		    THEN                                    leaf = nullptr;
		}
	}

public:

	// inserts new node with key and value
	inline iterator insert(const reference data)
	{
		ANYWAY                                      return iterator{ *this, insert(root, data), false };
	}

	// return optional data by key
	inline std::optional<value_type> find(const key_type& key) const
	{
		if      (pointer leaf{ find(root, key) })   return { leaf->data };
		else                                        return {};
	}

	// remove node by key
	inline bool erase(const iterator& pos)
	{
		ANYWAY                                      return erase(pos.value, (*pos).first);
	}

	// remove node by key
	inline bool erase(const key_type& key)
	{
		ANYWAY                                      return erase(root, key);
	}

	// remove all nodes
	inline void clear()
	{
		ANYWAY                                      clear(root);
	}

	// return number of nodes
	inline size_type size() const
	{
		ANYWAY                                      return size_count;
	}

	// return true if tree is empty
	inline bool empty() const
	{
		ANYWAY                                      return size_count == 0;
	}

	// return iterator of the first node
	inline iterator begin()
	{
		ANYWAY                                     return iterator{ *this, leftmost(root), false };
	}

	// return iterator of the post-last node
	inline iterator end()
	{
		ANYWAY                                     return iterator{ *this, nullptr, true };
	}

	// return value reference by key
	inline mapped_reference operator[](const key_type& key)
	{
		ANYWAY                                      pointer leaf{ find(root, key) };
		if      (!leaf)                             insert(std::make_pair(key, mapped_type{}));
		ANYWAY                                      return find(root, key)->data.second;
	}

	// create filled tree
	tree(std::initializer_list<value_type> init)
		: cmp{ key_compare{} }
		, size_count{ 0 }
	{
		for     (auto item : init)                  insert(root, item);
	}

	// create empty tree
	explicit tree()
		: root{ nullptr }
		, cmp{ key_compare{} }
		, size_count{ 0 } {}

};

RZD_END

#endif