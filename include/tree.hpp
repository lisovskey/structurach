/**
 * binary search tree class
 * created by lisovskey
 */

#ifndef TREE_H
#define TREE_H

#define RZD_BEGIN namespace rzd {
#define RZD_END }
#define ANYWAY
#define THEN

#include <list>
#include <memory>
#include <ostream>
#include <optional>

RZD_BEGIN

using std::list;
using std::ostream;
using std::optional;
using std::make_optional;

// binary search tree
template <typename T>
class Tree
{
    // prototype
    struct Node;

    // aliases
    using pointer = std::shared_ptr<Node>;
    using pair = std::pair<int, T>;

    // unit of tree
    struct Node {
        pair data;
        pointer left;
        pointer right;
		Node(pair data) : data{ data }, left{ nullptr }, right{ nullptr } {}
    };

    // start point
    pointer root;

	// IF       CONDITION                           ACTION

    pointer _insert(pointer leaf, const pair data)
    {
        if      (!leaf)                             return leaf = pointer(new Node(data));
        else if (data.first < leaf->data.first)     leaf->left = _insert(leaf->left, data);
        else if (data.first > leaf->data.first)     leaf->right = _insert(leaf->right, data);
        else                                        leaf->data.first = data.first;
        ANYWAY                                      return leaf;
    }

    pointer _find(const pointer leaf, const int key) const
    {
        if      (!leaf || leaf->data.first == key)  return leaf;
        else if (key < leaf->data.first)            return _find(leaf->left, key);
        else                                        return _find(leaf->right, key);
    }

    pointer _min(const pointer leaf) const
    {
        if      (leaf->left)                        return _min(leaf->left);
        else                                        return leaf;
    }

    pointer _remove(pointer leaf, const int key)
    {
        if      (!leaf)                             return leaf;
        else if (key < leaf->data.first)            leaf->left = _remove(leaf->left, key);
        else if (key > leaf->data.first)            leaf->right = _remove(leaf->right, key);
        else if (leaf->left && leaf->right) {
            THEN                                    leaf->data.first = (_min(leaf->right))->data.first;
            THEN                                    leaf->right = _remove(leaf->right, leaf->data.first);
        }
        else if (leaf->left)                        leaf = leaf->left;
        else if (leaf->right)                       leaf = leaf->right;
        else                                        leaf = nullptr;
        ANYWAY                                      return leaf;
    }

    int _size(const pointer leaf) const
    {
        if      (leaf)                              return _size(leaf->left) + 1 + _size(leaf->right);
		else                                        return 0;
    }

	ostream& _view(const pointer leaf, ostream& os) const
	{
		if		(leaf) {
			THEN									_view(leaf->left, os);
			THEN									os << leaf->data.second << "\n";
			THEN									_view(leaf->right, os);
		}
		ANYWAY										return os;
	}

	list<pair>& _get_list(const pointer leaf, list<pair>& list) const
	{
		if (leaf) {
			THEN									_get_list(leaf->left, list);
			THEN									list.push_back(leaf->data);
			THEN									_get_list(leaf->right, list);
		}
		ANYWAY										return list;
	}

public:

	// operators

	optional<T> operator[](const int key)
	{
		ANYWAY										return find(key);
	}

	friend ostream& operator<<(ostream& os, const Tree& tree)
	{
		ANYWAY										return tree._view(tree.root, os);
	}

    // constructors

	Tree() : root{ nullptr } {}

	Tree(const int key, const T value) : root{ new Node(pair(key, value)) } {}

    // usable methods

	// inserts new node with key and value
    void insert(const int key, const T value)
    {
        ANYWAY                                      root = _insert(root, pair(key, value));
    }

	// returns optional value by key
    optional<T> find(const int key) const
    {
        ANYWAY                                      pointer leaf = _find(root, key);
        if      (leaf)                              return make_optional(leaf->data.second);
        else                                        return {};
    }

	// removes node by key
    void remove(const int key)
    {
        ANYWAY                                      root = _remove(root, key);
    }

	// returns number of nodes
    int size() const
    {
        ANYWAY                                      return _size(root);
    }

	// returns sorted list 
	list<pair> get_list() const
	{
		ANYWAY										list<pair> list;
		ANYWAY										return _get_list(root, list);
	}
 
};

RZD_END

#endif