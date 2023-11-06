#include <cassert>
#include <iostream>
#include <set>
#include "tree.hpp"

namespace {
  const char KEY = 'k';
  const char QUERY = 'q';
} //namespace

int main() {
  Trees::Search_RBTree<int> tree{};
  
  for (;;) {
    char c;
    std::cin >> c;
    if (!std::cin)
      break;
    if (c == KEY) {
      int value;
      std::cin >> value;
      assert(std::cin.good());
      tree.rb_insert(value);
      //tree.print();
    }
    if (c == QUERY) {
      int fst, snd;
      std::cin >> fst >> snd;
      assert(std::cin.good());
      std::cout << tree.range_query(fst, snd) << " ";
    }
  }
  std::cout << std::endl;
}