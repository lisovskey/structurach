/*
 * iterator of binary search tree
 * created by lisovskey
 */

#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "tree.hpp"
#include <stdexcept>

namespace rzd {

    template <
        typename Key,
        typename T,
        typename Compare
    > class tree<Key, T, Compare>::iterator {

        using pointer = typename tree::pointer;
        using value_type = typename tree::value_type;

        const tree& tree_ref;
        bool is_end;

        pointer prev_parent(pointer leaf)
        {
            if (leaf->parent == nullptr)
                throw std::out_of_range("iterator went over the begin");
            else if (tree_ref.cmp(leaf->parent->data.first, leaf->data.first))				
                return leaf->parent;
            else
                return prev_parent(leaf->parent);
        }

        pointer next_parent(pointer leaf)
        {
            if (leaf->parent == nullptr)
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
                leaf = tree_ref.rightmost(tree_ref.root);
            else if (leaf == nullptr)
                throw std::out_of_range("iterator went wrong way");
            else if (leaf->left != nullptr)
                leaf = tree_ref.rightmost(leaf->left);
            else
                leaf = prev_parent(leaf);
            is_end = false;
            return *this;
        }

        iterator& operator++()
        {
            if (is_end)
                throw std::out_of_range("iterator went over the end");
            else if (leaf == nullptr)
                throw std::out_of_range("iterator went wrong way");
            else if (leaf->right != nullptr)
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

        value_type& operator*()
        {
            return leaf->data;
        }

        value_type* operator->()
        {
            return &leaf->data;
        }

        bool operator==(const iterator& it)
        {
            return leaf == it.leaf;
        }

        bool operator!=(const iterator& it)
        {
            return leaf != it.leaf;
        }

        iterator(const tree& tree_ref, pointer leaf)
            : tree_ref{ tree_ref }
            , leaf{ leaf }
        {
            is_end = leaf == nullptr;
        }

    };

}

#endif