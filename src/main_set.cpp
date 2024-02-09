#include <cassert>
#include <iostream>
#include <set>
#include "tree.hpp"
#include "tools.hpp"

using namespace yLab; //for types of requests

template <typename C, typename T> int range_query(const C &s, T fst, T snd) {
  if (fst >= snd)
    return 0;
    
  using itt = typename C::iterator;
  itt start = s.lower_bound(fst);
  itt fin = s.upper_bound(snd);
  return std::distance(start, fin);
}

int main() {
  std::set<int> s;
  
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
    } else if (c == QUERY) {
      int fst, snd;
      std::cin >> fst >> snd;
      assert(std::cin.good());
      std::cout << range_query(s, fst, snd) << " ";
    }
  }
  std::cout << std::endl;
}