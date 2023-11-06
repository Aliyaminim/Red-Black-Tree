#include "gtest/gtest.h"
#include "tree.hpp"
#include <cstdlib>

TEST(Test_lowerbound, Test1) {
    Trees::Search_RBTree<int> tree{}; 
    int x = (rand() % 50) + 1;
    int comp = x + (rand() % 5) + 1;
    for (int i = 0; i < 100; ++i) {
        int y = (rand() % 100) + 1;
        if ((y < x) && (y > comp))   
            tree.rb_insert(y);
    }
    tree.rb_insert(comp);
    ASSERT_TRUE(tree.lower_bound(x)->key == comp);
}

TEST(Test_lowerbound, Test2) {
    Trees::Search_RBTree<int> tree{}; 
    int x = (rand() % 50) + 1;
    int comp = x + (rand() % 5) + 1;
    for (int i = 0; i < 100; ++i) {
        int y = (rand() % 100) + 1;
        if ((y < x) && (y > comp))   
            tree.rb_insert(y);
    }
    tree.rb_insert(comp);
    ASSERT_TRUE(tree.lower_bound(x)->key == comp);
}

TEST(Test_upperbound, Test1) {
    Trees::Search_RBTree<int> tree{}; 
    int x = (rand() % 50) + 1;
    int comp = x + (rand() % 5) + 1;
    for (int i = 0; i < 100; ++i) {
        int y = (rand() % 100) + 1;
        if ((y < x) && (y > comp))   
            tree.rb_insert(y);
    }
    tree.rb_insert(comp);
    tree.rb_insert(x);
    ASSERT_TRUE(tree.upper_bound(x)->key == comp);
}

TEST(Test_upperbound, Test2) {
    Trees::Search_RBTree<int> tree{}; 
    int x = (rand() % 50) + 1;
    int comp = x + (rand() % 5) + 1;
    for (int i = 0; i < 100; ++i) {
        int y = (rand() % 100) + 1;
        if ((y < x) && (y > comp))   
            tree.rb_insert(y);
    }
    tree.rb_insert(comp);
    ASSERT_TRUE(tree.upper_bound(x)->key == comp);
}

TEST(Test_rangequery, Test1) {
    Trees::Search_RBTree<int> tree{};
    srand(time(NULL));

    for (int i = 0; i < 20; ++i) {
        int x = (rand() % 1000); //0-999
        tree.rb_insert(x);
        srand(time(NULL));
        x = (rand() % 1000) + 1000; //1000-1999
        tree.rb_insert(x);
        srand(time(NULL));
        x = (rand() % 10000) + 10000;
        tree.rb_insert(x);
    }
    ASSERT_TRUE(tree.range_query(1000, 1999) == 20);
}

TEST(Test_rangequery, Test2) {
    Trees::Search_RBTree<int> tree{};
    srand(time(NULL));

    for (int i = 0; i < 30; ++i) {
        int x = (rand() % 1000); //0-999
        tree.rb_insert(x);
        x = (rand() % 1000) + 1000; //1000-1999
        tree.rb_insert(x);
    }
    ASSERT_TRUE(tree.range_query(1000, 1999) == 30);
}

TEST(Test_rangequery, Test3) {
    Trees::Search_RBTree<int> tree{};
    srand(time(NULL));

    for (int i = 0; i < 30; ++i) {
        int x = (rand() % 100); //0-99
        tree.rb_insert(x);
        x = (rand() % 100) + 100; //100-199
        tree.rb_insert(x);
    }

    ASSERT_TRUE(tree.range_query(0, 200) == 60);
}


