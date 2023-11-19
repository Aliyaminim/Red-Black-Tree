#pragma once

#include <iostream>
#include <cstdlib>
#include <list>
#include <iterator>
#include <cassert>
#include <climits>

namespace Trees {

enum class color_type { red, black };

template <typename KeyT>
class Search_RBTree final {

    struct Node {
        KeyT key;
        typename std::list<Node>::iterator parent, left, right;
        color_type color = color_type::red;

        Node() = default;
        Node(KeyT key_, typename std::list<Node>::iterator default_it) : key(key_), parent(default_it),
                                                            left(default_it), right(default_it) {};
    };


    using NodeIt = typename std::list<Node>::iterator;

    std::list<Node> node_storage;
    NodeIt nil = node_storage.end(); //leaves in tree
    NodeIt root = nil;

public:
    //constructor
    Search_RBTree() {
        node_storage.emplace_back();
        nil = std::prev(node_storage.end());
        nil->color = color_type::black; //constructing leaves in tree
        nil->key = INT_MAX;
        root = nil;
    }  

private:

    int size_of_childtree(NodeIt node) const{
        if (node == nil) {
            return 0;
        }
        return size_of_childtree(node->left) + 1 + size_of_childtree(node->right);
    }

    NodeIt common_ancestor(const NodeIt start, const NodeIt fin, const NodeIt curr_root) const {             
        if ((start->key <= curr_root->key) && (curr_root->key <= fin->key))
            return curr_root;
        else if ((start->key < curr_root->key) && (fin->key < curr_root->key))
            return common_ancestor(start, fin, curr_root->left);
        else if ((curr_root->key < start->key) && (curr_root->key < fin->key))
            return common_ancestor(start, fin, curr_root->right);
        else {
            assert("fix your code now!");
            return nil;
        }
    }

    //auxiliary function for lower_bound() and upper_bound()
    void bound_helper(NodeIt node, const KeyT key, NodeIt &res, int mode) const {
        if (node == nil)
            return;

        if (key == node->key) {
            if (mode == 0) {
                //lower_bound()
                res = node;
                return;
            } else if (mode == 1) {
                //upper_bound()
                bound_helper(node->right, key, res, mode);
                return;
            } else
                assert("fix your code now!");
        } else if (key < node->key) {
            bound_helper(node->left, key, res, mode);
            if (res == nil) {
                //nothing better was found
                res = node;
            }
            return;
        } else if (key > node->key) {
            bound_helper(node->right, key, res, mode);
            if (res == nil)
                //nothing to offer
            return;
        }
    }

public: //селекторы

    //not less than key
    NodeIt lower_bound(const KeyT key) const {
        NodeIt res = nil;
        bound_helper(root, key, res, 0);

        return res;
    }

    //greater
    NodeIt upper_bound(const KeyT key) const {
        NodeIt res = nil;
        bound_helper(root, key, res, 1);

        return res;
    }

    int mydistance(const NodeIt start, const NodeIt fin) const {
        if (start == nil)
            return 0;

        int dist = 0;
        
        NodeIt anc = common_ancestor(start, fin, root);
        NodeIt i = anc;

        while (i != start) {
            if (start->key < i->key) {
                if (i != anc)
                    dist += size_of_childtree(i->right);

                i = i->left;
                if (i->key >= start->key)
                    dist++;
            } else {
                i = i->right;
                if (i->key >= start->key)
                    dist++;
            }
        }

        if (start != anc)
            dist += size_of_childtree(start->right);

        i = anc;
        while (i != fin) {
            if (fin->key >= i->key) {
                if (i != anc)
                    dist += size_of_childtree(i->left);

                i = i->right;         
                if (i->key <= fin->key)
                    dist++;
            } else {
                i = i->left;
                if (i->key <= fin->key)
                    dist++;
            }
        }
        if (fin != anc && fin != nil)
            dist += size_of_childtree(fin->left);
        
        return dist;
    }

    int range_query(const KeyT fst, const KeyT snd) const {
        if(fst >= snd)
            return 0;

        NodeIt start = lower_bound(fst);
        NodeIt fin = upper_bound(snd);   
        return mydistance(start, fin);
    }

private: 

    bool is_left_child(const NodeIt node) const {
        assert((node != nil) && (node->parent != nil));
        return node == node->parent->left;
    }

    bool is_red(const NodeIt node) const {
        return node->color == color_type::red;
    }

    NodeIt grandparent(const NodeIt node) const {
        return node->parent->parent;
    }

    NodeIt uncle(const NodeIt node) const {
        if (is_left_child(node))
            return node->parent->right;
        else 
            return node->parent->left;
    }

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

        //set new x's left child
        x->left = y->right; 
        if(y->right != nil)
            y->right->parent = x;
        
        //set new y's parent 
        y->parent = x->parent; 
        if(x->parent == nil)
            root = y;
        else if (is_left_child(x))
            x->parent->left = y;
        else    
            x->parent->right = y;

        //set new y's right child
        y->right = x;

        //set new x's parent
        x->parent = y;
    }

/* right_rotate(y)
    |       |
    y  ==>  x  
   /         \
  x   <==     y
  left_rotate(x)
*/
    void left_rotate(NodeIt x) {
        NodeIt y = x->right;
        //set new x's right child
        x->right = y->left;
        if (y->left != nil)
            y->left->parent = x;
        
        //set new y's parent
        y->parent = x->parent;
        if (x->parent == nil)
            root = y;
        else if (is_left_child(x))
            x->parent->left = y;
        else 
            x->parent->right = y;

        //set new y's left child
        y->left = x;
        //set new x's parent
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
        while (is_red(z->parent)) {
            y = uncle(z->parent);
            if (is_red(y)) {
                z->parent->color = color_type::black;
                y->color = color_type::black;
                grandparent(z)->color = color_type::red;
                z = grandparent(z);
            } else {
                NodeIt tmp = z->parent;
                if (is_left_child(z->parent) && !is_left_child(z)) {
                    z = z->parent;
                    left_rotate(z);
                } else if (!is_left_child(z->parent) && is_left_child(z)) {
                    z = z->parent;
                    right_rotate(z);
                }
                z->parent->color = color_type::black;
                grandparent(z)->color = color_type::red;

                if (is_left_child(tmp))
                    right_rotate(grandparent(z));
                else
                    left_rotate(grandparent(z));
            }
        } //while
        root->color = color_type::black;
    }

    //insert new node with given key and balance red-black tree
    void rb_insert(const KeyT key) {
        node_storage.emplace_back(key, nil); 
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

