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
#include <optional>

RZD_BEGIN

using std::list;
using std::optional;

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

	//	IF      CONDITION                           ACTION

	void insert(pointer& leaf, const pair data)
	{
		if      (!leaf)                             leaf = pointer{ new Node{ data } };
		else if (data.first < leaf->data.first)     insert(leaf->left, data);
		else if (data.first > leaf->data.first)     insert(leaf->right, data);
		else                                        leaf->data.first = data.first;
	}

	pointer find(const pointer& leaf, const int key) const
	{
		if      (!leaf || leaf->data.first == key)  return leaf;
		else if (key < leaf->data.first)            return find(leaf->left, key);
		else                                        return find(leaf->right, key);
	}

	pointer minimum(const pointer& leaf) const
	{
		if      (leaf->left)                        return minimum(leaf->left);
		else                                        return leaf;
	}

	void remove(pointer& leaf, const int key)
	{
		if      (!leaf)                             return;
		else if (key < leaf->data.first)            remove(leaf->left, key);
		else if (key > leaf->data.first)            remove(leaf->right, key);
		else if (leaf->left && leaf->right) {
		    THEN                                    leaf->data.first = minimum(leaf->right)->data.first;
		    THEN                                    remove(leaf->right, leaf->data.first);
		}
		else if (leaf->left)                        leaf = leaf->left;
		else if (leaf->right)                       leaf = leaf->right;
		else                                        leaf = nullptr;
	}

	void clear(pointer& leaf)
	{
		if      (leaf) {
		    THEN                                    clear(leaf->left);
		    THEN                                    clear(leaf->right);
		    THEN                                    leaf = nullptr;
		}
	}

	int size(const pointer& leaf) const
	{
		if      (leaf)                              return size(leaf->left) + 1 + size(leaf->right);
		else                                        return 0;
	}

	list<pair>& get_list(const pointer& leaf, list<pair>& list) const
	{
		if      (leaf) {
		    THEN                                    get_list(leaf->left, list);
		    THEN                                    list.push_back(leaf->data);
		    THEN                                    get_list(leaf->right, list);
		}
		ANYWAY                                      return list;
	}

public:

	// inserts new node with key and value
	inline void insert(const int key, const T& value)
	{
		ANYWAY                                      insert(root, pair{ key, value });
	}

	// returns optional value by key
	inline optional<T> find(const int key) const
	{
		if      (pointer leaf = find(root, key))    return { leaf->data.second };
		else                                        return {};
	}

	// removes node by key
	inline void remove(const int key)
	{
		ANYWAY                                      remove(root, key);
	}

	inline void clear()
	{
		ANYWAY                                      clear(root);
	}

	// returns number of nodes
	inline int size() const
	{
		ANYWAY                                      return size(root);
	}

	// returns sorted list 
	inline list<pair> get_list() const
	{
		ANYWAY                                      return get_list(root, list<pair>());
	}

	// returns optional value by key
	inline optional<T> operator[](const int key)
	{
		ANYWAY                                      return find(key);
	}

	// constructors

	Tree() : root{ nullptr } {}

	Tree(const int key, const T& value) : root{ new Node{ pair{ key, value } } } {}

};

RZD_END

#endif