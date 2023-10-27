#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <cassert>

//store all nodes in std::vector, because it will delete and copy with no problems;
//iterators or pointers
//find why segfault


namespace Trees {

enum class color_type { red, black };

template <typename KeyT>
class Search_RBTree {

    struct Node {
        KeyT key;
        typename std::vector<Node>::iterator parent, left, right;
        //int black_height = 0;
        color_type color = color_type::red;

        Node() = default;
        Node(KeyT key_, typename std::vector<Node>::iterator default_it) : key(key_), parent(default_it),
                                                            left(default_it), right(default_it) {};
    };


    using NodeIt = typename std::vector<Node>::iterator;

    std::vector<Node> node_storage;
    NodeIt nil = node_storage.end(); //leaves in tree
    //NodeIt root = nil;

public:
    NodeIt root = nil; //temporarily
    //constructor
    Search_RBTree() {
        node_storage.emplace_back();
        nil = std::prev(node_storage.end());
        nil->color = color_type::black; //constructing leaves in tree
        root = nil;
    }

public: // селекторы
    /*Node* find(const KeyT key) {
        Node* x 
    }*/
    


    //Node* lower_bound(KeyT key) const; O(log N)
    //Node* upper_bound(KeyT key) const;
    //int distance(Node* fst, Node* snd) const;
public: // модификаторы

/* right_rotate(x)
    |       |
    x  ==>  y  
   /         \
  y   <==     x
  left_rotate(y)
*/
    void right_rotate(NodeIt x) {
        NodeIt y = x->left;
        x->left = y->right;
        if(y->right != nil)
            y->right->parent = x;
        
        y->parent = x->parent;
        if(x->parent == nil)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else    
            x->parent->right = y;
        y->right = x;
        x->parent = y;
    }

    void left_rotate(NodeIt x) {
        NodeIt y = x->right;
        x->right = y->left;
        if (y->left != nil)
            y->left->parent = x;
        
        y->parent = x->parent;
        if (x->parent == nil)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else 
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void tree_insert(const KeyT key) {
        NodeIt new_node = std::prev(node_storage.end());
        NodeIt y = nil;
        NodeIt x = root;

        while (x != nil) {
            y = x;
            assert((key != x->key) && "oops, repetitive keys aren't expected");
            if (key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        new_node->parent = y;
        if (y == nil)
            root = new_node; //tree was empty
        else if (key < y->key)
            y->left = new_node;
        else 
            y->right = new_node;
    }

    void tree_balance() {
        NodeIt new_node = std::prev(node_storage.end());
        NodeIt y = nil;
        NodeIt z = new_node;
        while (z->parent->color == color_type::red) {
            if (z->parent == z->parent->parent->left) {
                y = z->parent->parent->right;
                if (y->color == color_type::red) {
                    z->parent->color = color_type::black;
                    y->color = color_type::black;
                    z->parent->parent->color = color_type::red;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->color = color_type::black;
                    z->parent->parent->color = color_type::red;
                    right_rotate(z->parent->parent);
                }
            } else {
                y = z->parent->parent->left;
                if (y->color == color_type::red) {
                    z->parent->color = color_type::black;
                    y->color = color_type::black;
                    z->parent->parent->color = color_type::red;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->color = color_type::black;
                    z->parent->parent->color = color_type::red;
                    left_rotate(z->parent->parent);
                }
            }
        } //while
        root->color = color_type::black;
    }

    //insert new node with given key and balance red-black tree
    void rb_insert(const KeyT key) {
        node_storage.emplace_back(key, nil); //new_node is always in the end of node_storage
        tree_insert(key);
        tree_balance();
    }

    void print_2(NodeIt x, int space) {
        if (x != nil) {
            space += 10;
            print_2(x->right, space);
            std::cout << std::endl;
            for (int i = 10; i < space; i++)
                std::cout << " ";
            std::cout << x->key;
            if (x->color == color_type::black)
                std::cout << "b" << std::endl;
            else
                std::cout << "r" << std::endl;
            print_2(x->left, space);
        }
    }

    void print() {
        print_2(root, 0);
    }
}; //class Search_RBTree
} //namespace Trees

