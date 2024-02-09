#include "gtest/gtest.h"
#include "tree.hpp"
#include <cstdlib>

using namespace yLab;

TEST (Constructors, Default_Constructor)
{
    const Trees::Search_RBTree<int> tree;
    EXPECT_EQ (tree.size(), 0);
    EXPECT_TRUE (tree.empty());
}
