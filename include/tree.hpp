#pragma once

#include <iostream>
#include <cstdlib>
#include <list>
#include <iterator>
#include <cassert>
#include <utility>
#include <iterator>

namespace yLab {
struct unknown_query : public std::runtime_error {
    unknown_query(const char *message = "Given rank must be positive\n")
              : std::runtime_error{message} {};
};

struct seg_fault : public std::runtime_error {
    seg_fault(const char *message = "Going outside the bounds of the tree\n")
              : std::runtime_error{message} {};
};

namespace Trees {

enum class color_type { red, black };
enum class bound_type { lwbound_mode, upbound_mode };

template <typename KeyT>
class Search_RBTree final {
private:
    struct Node final {
        KeyT key;
        typename std::list<Node>::iterator parent, left, right;
        color_type color;
        int subtree_size;

        Node(KeyT key_, typename std::list<Node>::iterator default_it, color_type color_ = color_type::red, int subtree_size_ = 1) : 
            key(key_), parent(default_it), left(default_it), right(default_it), color(color_), subtree_size(subtree_size_) {};

    };

    using NodeIt = typename std::list<Node>::iterator;
    using CNodeIt = typename std::list<Node>::const_iterator;

    std::list<Node> node_storage;
    NodeIt nil = node_storage.end(); //leaves in tree
    NodeIt root = nil;

public:
    //constructor
    Search_RBTree() {
        node_storage.emplace_back(KeyT{}, node_storage.end(), color_type::black, 0);
        nil = node_storage.begin(); //leaves in tree
        root = nil;
    } 

    //capacity 
    bool empty() const noexcept { return root == nil; }
    int size() const noexcept { return (empty()) ? 0 : root->subtree_size + 1; } 

private:

    CNodeIt common_ancestor(const CNodeIt start, const CNodeIt fin, const CNodeIt curr_root) const { 
        if (fin == nil) {
            if (start->key <= curr_root->key)
                return curr_root;
            else 
                return common_ancestor(start, fin, curr_root->right);
        }

        if ((start->key <= curr_root->key) && (curr_root->key <= fin->key))
            return curr_root;
        else if ((start->key < curr_root->key) && (fin->key < curr_root->key))
            return common_ancestor(start, fin, curr_root->left);
        else if ((curr_root->key < start->key) && (curr_root->key < fin->key))
            return common_ancestor(start, fin, curr_root->right);
        else 
            return nil;
    }

    //auxiliary function for lower_bound() and upper_bound()
    CNodeIt bound_impl(const KeyT &key, bound_type mode) const {
        CNodeIt res = nil;
        CNodeIt node = root;
        while (node != nil) {
            if (key < node->key) {
                res = std::exchange(node, node->left);
            } else if (node->key < key) {
                node = node->right; 
            } else {
            if (mode == bound_type::lwbound_mode) {
                    return node;
                } else {
                    node = node->right;
                } 
            }
        }
        return res;
    }

    int mydistance(const CNodeIt start, const CNodeIt fin) const {
        if (start == nil)
            return 0;

        int dist = 0;
        
        CNodeIt anc = common_ancestor(start, fin, root);
        CNodeIt i = anc;

        while (i != start) {
            if (start->key < i->key) {
                if (i != anc)
                    dist += i->right->subtree_size;

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
            dist += start->right->subtree_size;

        if (fin != nil) {
            i = anc;
            while (i != fin) {
                if (fin->key >= i->key) {
                    if (i != anc)
                        dist += i->left->subtree_size;

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
                dist += fin->left->subtree_size;
        } else    
            dist += anc->right->subtree_size + 1;
        
        return dist;
    }

    CNodeIt select_impl(int i) const {
        if ((i < 1) || (i > size()))
            throw unknown_query{};

        CNodeIt curr_elem = root;
        while (curr_elem != nil) {
            int curr_rank = curr_elem->left->subtree_size + 1;
            if (i == curr_rank)
                return curr_elem;
            else if (i < curr_rank)
                curr_elem = curr_elem->left;
            else {
                i -= curr_rank;
                curr_elem = curr_elem->right;
            }
        }
        throw unknown_query{};
    }

public: 
    //not less than key
    CNodeIt lower_bound(const KeyT &key) const {
        return bound_impl(key, bound_type::lwbound_mode);
    }

    //greater
    CNodeIt upper_bound(const KeyT &key) const {
        return bound_impl(key, bound_type::upbound_mode);
    }

    /* counts number of nodes in tree such that their keys all lie strictly between left and right boundaries, inclusive.*/
    int range_query(const KeyT &fst, const KeyT &snd) const {
        if  (!(fst < snd)) 
            return 0;

        const CNodeIt start = lower_bound(fst);
        const CNodeIt fin = upper_bound(snd);   
        return mydistance(start, fin);
    }

    /* i-th smallest element, if request is for the smallest element with a number greater than 
        the total number of elements in the tree, simply return the last smallest (that is, the largest) */
    KeyT select_ranked_elem(int i) const {
        if (i > root->subtree_size) 
            i = root->subtree_size;
        return select_impl(i)->key;
    }

    CNodeIt operator[](int i) const {
        if (empty() || (i < 0) || (i >= size())) 
            throw seg_fault{};

        int ith_smallest_el = i + 1;
        return select_impl(kth_smallest_el);
    }

    //counts number of elements that are less than given key
    int key_rank(const KeyT &key) const {
        CNodeIt node_bound = lower_bound(key);
        if (node_bound == nil)
            return root->subtree_size;

        KeyT key_bound = node_bound->key;
        CNodeIt curr_root = root;
        int rank = 0;

        while (key_bound != curr_root->key) {
            if (key_bound < curr_root->key) {
                curr_root = curr_root->left;
            } else if (curr_root->key < key_bound) {
                rank += curr_root->left->subtree_size + 1;
                curr_root = curr_root->right;
            }
        }
        rank += curr_root->left->subtree_size;

        return rank; 
    }

private: 

    bool is_left_child(const CNodeIt node) const {
        assert(node != nil);
        assert(node->parent != nil);
        return node == node->parent->left;
    }

    bool is_red(const CNodeIt node) const {
        return node->color == color_type::red;
    }

    NodeIt grandparent(const CNodeIt node) const {
        return node->parent->parent;
    }

    NodeIt uncle(const CNodeIt node) const {
        if (is_left_child(node))
            return node->parent->right;
        else 
            return node->parent->left;
    } 

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

        y->subtree_size = x->subtree_size;
        x->subtree_size = x->left->subtree_size + x->right->subtree_size + 1;
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

        y->subtree_size = x->subtree_size;
        x->subtree_size = x->left->subtree_size + x->right->subtree_size + 1;
    }

    void tree_balance() {
        NodeIt y = nil;
        NodeIt z = std::prev(node_storage.end());

        while (is_red(z->parent)) {
            y = uncle(z->parent);
            if (is_red(y)) {
                z->parent->color = color_type::black;
                y->color = color_type::black;
                grandparent(z)->color = color_type::red;
                z = grandparent(z);
            } else {
                CNodeIt tmp = z->parent;
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

    std::pair<NodeIt, NodeIt> find_pos_to_insert(const KeyT &key) {
        NodeIt parent = nil;
        NodeIt node = root;

        while (node != nil) {        
            if (key < node->key) 
                parent = std::exchange(node, node->left);
            else if (node->key < key) 
                parent = std::exchange(node, node->right);
            else 
                break;
        }

        return std::pair{node, parent};
    }

    CNodeIt insert_impl(const KeyT &key, NodeIt parent) {
        node_storage.emplace_back(key, nil); 
        NodeIt new_node = std::prev(node_storage.end());

        for (NodeIt node = parent; node != root; node = node->parent) 
            node->subtree_size++;   
        if (!empty())
            root->subtree_size++;

        new_node->parent = parent;
        if (empty())
            root = new_node; 
        else if (key < parent->key)
            parent->left = new_node;
        else 
            parent->right = new_node;

        tree_balance();
        return new_node;
    }

public:

    //insert new node with given key and balance red-black tree
    std::pair<CNodeIt, bool> insert(const KeyT &key) {
        auto [node, parent] = find_pos_to_insert(key);
        if (node == nil) {
            CNodeIt new_node = insert_impl(key, parent);
            return std::pair{new_node, true};
        } else {
            return std::pair{node, false};
        }
    }

    void print_impl(const CNodeIt x, int space) const {
        if (x != nil) {
            space += 10;
            print_impl(x->right, space);
            std::cout << std::endl;
            for (int i = 10; i < space; i++)
                std::cout << " ";
            std::cout << x->key;
            if (x->color == color_type::black)
                std::cout << "b" << std::endl;
            else
                std::cout << "r" << std::endl;
            
            print_impl(x->left, space);
        }
    }

    void print() const {
        print_impl(root, 0);
    }

}; //class Search_RBTree
} //namespace Trees
} //namespace yLab

