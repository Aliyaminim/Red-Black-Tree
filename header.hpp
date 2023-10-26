#pragma once

#include <iostream>
#include <cstdlib>

//store all nodes in std::vector, because it will delete and copy with no problems;
//iterators or pointers


namespace Trees {

enum class color_type { red, black };

template <typename KeyT>
class Search_RBTree {
    struct Node {
        KeyT key;
        Node *parent, *left, *right;
        //int black_height = 0;
        color_type color = color_type::red;

        Node() = default;
        Node(KeyT key_, Node* default_ptr = nullptr) : key(key_), parent(default_ptr), left(default_ptr),
                                                       right(default_ptr);
        ~Node() { delete left; delete right;}
    }
    //constructing leaves in tree
    Node nil_leaf{};
    nil_leaf.color = black;
    Node* nil = &nil_leaf;
    //does parent of root need to be assigned to nil?

    Node* root = nil;

    //rotation flags

public: // селекторы
    //Search_RBTree()
    iterator lower_bound(KeyT key) const;
    iterator upper_bound(KeyT key) const;
    int distance(iterator fst, iterator snd) const;
public: // модификаторы
    void tree_insert(const KeyT key) {
        Node* y = nil;
        Node* x = root;

        while (x != nil) {
            y = x;
            if (key < x.key)
                x = x->left;
            else if (x->key == key) 
                std::cout << "oops, repetitive keys aren't expected"
            else
                x = x->right;
        }
        new_node.parent = y;
        if (y == nil)
            root = &new_node; //tree was empty
        else if (key < y->key)
            y->left = &new_node;
        else 
            y->right = &new_node;
    }
    void tree_balance 

    void rb_insert(const KeyT key) {
        Node* new_node = new Node{key, nil};
        tree_insert(&new_node);
        tree_balance(tree_insert(key));
    }
}
} //namespace Trees

