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

    switch(c) {
      case KEY:
        int value;
        std::cin >> value;
        assert(std::cin.good());
        tree.insert(value);
        break;

      case QUERY:
        int fst, snd;
        std::cin >> fst >> snd;
        assert(std::cin.good());
        std::cout << tree.range_query(fst, snd) << " ";
        break;

      case SELECT:
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
        break;
      
      case RANK:
        int bound;
        std::cin >> bound;
        assert(std::cin.good());
        std::cout << tree.key_rank(bound) << " ";
        break;
    }
  }

  std::cout << std::endl;
  return ret;
}
