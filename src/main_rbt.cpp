#include <cassert>
#include <iostream>
#include <set>
#include <unordered_map>
#include "tree.hpp"

namespace {
  const char KEY = 'k';
  const char QUERY = 'q';
} //namespace

int main() {
  Trees::Search_RBTree<int> tree{};
  std::unordered_map<int, int> hash_input;
  
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
        tree.rb_insert(value);
        hash_input.emplace(value, value);
      }
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