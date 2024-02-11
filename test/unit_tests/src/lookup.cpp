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

TEST(Lookup, find) {
    Trees::Search_RBTree<int> tree{}; 
    for (int i = 0; i < 10; i++)
        tree.insert(i);
    for (int i = 0; i < 10; i++)
        EXPECT_EQ(tree.find(i)->key, i);
}

TEST(Lookup, contains) {
    Trees::Search_RBTree<int> tree{}; 
    for (int i = 0; i < 10; i++)
        tree.insert(i);
    for (int i = 0; i < 10; i++)
        EXPECT_TRUE(tree.contains(i));
    
    Trees::Search_RBTree<int> tree_empty{}; 
    EXPECT_FALSE(tree_empty.contains(0));
}

TEST(Lookup, nth_smallest) {
    Trees::Search_RBTree<int> tree{}; 
    for (int i = 1; i <= 10; i++)
        tree.insert(i);
    for (int i = 1; i <= 10; i++)
        EXPECT_EQ(tree.select_ranked_elem(i), i);

    EXPECT_EQ(tree.select_ranked_elem(11), 10);
}

TEST(Lookup, n_less_than) {
    Trees::Search_RBTree<int> tree{}; 
    for (int i = 1; i < 10; i += 2)
        tree.insert(i);
    int kol = 1;
    for (int i = 2; i < 11; i += 2, kol++) 
        EXPECT_EQ(tree.key_rank(i), kol);

    EXPECT_EQ(tree.key_rank(11), 5);
}

TEST(Lookup, range_query) {
    Trees::Search_RBTree<double> tree{};
    for (double i = 1; i < 10; i++)
        tree.insert(i/2);
    EXPECT_EQ(tree.range_query(1, 2), 3);
    EXPECT_EQ(tree.range_query(1, 4), 7);
}