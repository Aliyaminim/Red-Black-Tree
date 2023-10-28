#include "gtest/gtest.h"
#include "tree.hpp"
#include <cstdlib>

TEST(Test_lowerbound, Test1) {
    Trees::Search_RBTree<int> tree{}; 
    int x = (rand() % 100) + 1;
    for (int i = 0; i < 100; ++i) {
        int y = (rand() % 100) + 1;
        tree.rb_insert(y);
        assert((y != x) || (y != (x+1)));
    }
    tree.rb_insert(x+2);
    ASSERT_TRUE(tree.lower_bound(x)->key == (x+2));
}
