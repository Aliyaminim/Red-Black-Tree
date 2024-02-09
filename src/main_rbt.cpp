#include <cassert>
#include <iostream>
#include <set>
#include <unordered_map>
#include "tree.hpp"

using namespace yLab; 

int main() {
  Trees::Search_RBTree<int> tree{};
  std::unordered_map<int, int> hash_input;
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
      if (hash_input.find(value) == hash_input.end()) {
        tree.insert(value);
        hash_input.emplace(value, value);
      }
      //tree.print();
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