#include <cassert>
#include <iostream>
#include <set>
#include "tree.hpp"
#include "tools.hpp"

using namespace yLab; 

int main() {
  Trees::Search_RBTree<int> tree{};
  int ret = 0;
  
  for (;;) {
    char c;
    std::cin >> c;
    if (!std::cin)
      break;
    if (c == KEY) {
      int value;
      std::cin >> value;
      assert(std::cin.good());
      tree.insert(value);
    } else if (c == QUERY) {
      int fst, snd;
      std::cin >> fst >> snd;
      assert(std::cin.good());
      std::cout << tree.range_query(fst, snd) << " ";
    } else if (c == SELECT) {
      int i;
      std::cin >> i;
      assert(std::cin.good());
      try {
        std::cout << tree.select_ranked_elem(i) << " ";
      }
      catch(unknown_query &err) {
        std::cerr << err.what();
        ret = 1;
      }
    } else if (c == RANK) {
      int bound;
      std::cin >> bound;
      assert(std::cin.good());
      std::cout << tree.key_rank(bound) << " ";
    }
  }
  std::cout << std::endl;
  return ret;
}