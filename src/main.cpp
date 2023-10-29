#include <cassert>
#include <iostream>
#include <set>
#include "tree.hpp"

//статическая функция
namespace {
const char KEY = 'k';
const char QUERY = 'q';
} // namespace

template <typename C, typename T> int range_query(const C &s, T fst, T snd) {
  using itt = typename C::iterator;
  itt start = s.lower_bound(fst);
  itt fin = s.upper_bound(snd);
  return mydistance(start, fin);
}

int main() {
  Trees::Search_RBTree<int> tree{}; 
  //assert(tree.nil->color == Trees::color_type::black);
  //assert(tree.root != nullptr);

  for (;;) {
    int value;
    std::cin >> value;
    if (!std::cin)
      break;
    assert(std::cin.good());
    tree.rb_insert(value);
  }
  tree.print();
  
  std::cout << tree.upper_bound(5)->key << std::endl;
  //std::cout << tree.range_query(1, 5) << std::endl;

  //std::cout << tree.lower_bound(3)->key << std::endl;
  //tree.dump_tree();
  /*std::set<int> s;
  for (;;) {
    char c;
    std::cin >> c;
    if (!std::cin)
      break;
    if (c == KEY) {
      int value;
      std::cin >> value;
      assert(std::cin.good());
      s.insert(value);
    }
    if (c == QUERY) {
      int fst, snd;
      std::cin >> fst >> snd;
      assert(std::cin.good());
      std::cout << range_query(s, fst, snd) << " ";
    }
  }
  std::cout << std::endl;*/
}