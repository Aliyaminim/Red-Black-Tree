#include "gtest/gtest.h"
#include "tree.hpp"
#include <cstdlib>

using namespace yLab;

TEST(Test_lowerbound, Test1) {
    Trees::Search_RBTree<int> tree{}; 
    int x = (rand() % 50) + 1;
    int comp = x + (rand() % 5) + 1;
    for (int i = 0; i < 100; ++i) {
        int y = (rand() % 100) + 1;
        if ((y < x) && (y > comp))   
            tree.insert(y);
    }
    tree.insert(comp);
    ASSERT_TRUE(tree.lower_bound(x)->key == comp);
}

TEST(Test_lowerbound, Test2) {
    Trees::Search_RBTree<int> tree{}; 
    int x = (rand() % 50) + 1;
    int comp = x + (rand() % 5) + 1;
    for (int i = 0; i < 100; ++i) {
        int y = (rand() % 100) + 1;
        if ((y < x) && (y > comp))   
            tree.insert(y);
    }
    tree.insert(comp);
    ASSERT_TRUE(tree.lower_bound(x)->key == comp);
}

TEST(Test_upperbound, Test1) {
    Trees::Search_RBTree<int> tree{}; 
    int x = (rand() % 50) + 1;
    int comp = x + (rand() % 5) + 1;
    for (int i = 0; i < 100; ++i) {
        int y = (rand() % 100) + 1;
        if ((y < x) && (y > comp))   
            tree.insert(y);
    }
    tree.insert(comp);
    tree.insert(x);
    ASSERT_TRUE(tree.upper_bound(x)->key == comp);
}

TEST(Test_upperbound, Test2) {
    Trees::Search_RBTree<int> tree{}; 
    int x = (rand() % 50) + 1;
    int comp = x + (rand() % 5) + 1;
    for (int i = 0; i < 100; ++i) {
        int y = (rand() % 100) + 1;
        if ((y < x) && (y > comp))   
            tree.insert(y);
    }
    tree.insert(comp);
    ASSERT_TRUE(tree.upper_bound(x)->key == comp);
}



