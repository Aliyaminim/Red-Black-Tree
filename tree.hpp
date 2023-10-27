#pragma once

#include <iostream>
#include <cstdlib>

//store all nodes in std::vector, because it will delete and copy with no problems;
//iterators or pointers
//find why segfault


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
                                                       right(default_ptr) {};
        ~Node() { delete left; delete right;}
    };
    //Node* nil = nullptr;
    //Node* root = nullptr;

public:
    Node* nil = nullptr;
    Node* root = nullptr;

    //constructor
    Search_RBTree(Node* nil_ = new Node()): nil(nil_) {
        nil->color = color_type::black; //constructing leaves in tree
        root = nil;
    }

public: // селекторы
    //Search_RBTree()
    //Node* lower_bound(KeyT key) const;
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
    void right_rotate(Node* x) {
        Node* y = x->left;
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
    void left_rotate(Node* x) {
        Node* y = x->right;
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
    void tree_insert(Node* new_node, const KeyT key) {
        Node* y = nil;
        Node* x = root;

        while (x != nil) {
            y = x;
            if (key < x->key)
                x = x->left;
            else if (x->key == key) 
                std::cout << "oops, repetitive keys aren't expected" << std::endl;
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
    void tree_balance(Node* new_node) {
        Node* y = nil;
        Node* z = new_node;
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

    void rb_insert(const KeyT key) {
        Node* new_node = new Node(key, nil);
        tree_insert(new_node, key);
        tree_balance(new_node);
    }
};
} //namespace Trees

