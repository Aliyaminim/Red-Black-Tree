#include <cassert>
#include <iostream>
#include <set>

namespace {
  const char KEY = 'k';
  const char QUERY = 'q';
} //namespace

template <typename C, typename T> int range_query(const C &s, T fst, T snd) {
  using itt = typename C::iterator;
  itt start, fin;
  if (fst <= snd) {         
    start = s.lower_bound(fst);
    fin = s.upper_bound(snd);
  } else {    
    start = s.lower_bound(snd);
    fin = s.upper_bound(fst);
  }
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
    }
    if (c == QUERY) {
      int fst, snd;
      std::cin >> fst >> snd;
      assert(std::cin.good());
      std::cout << range_query(s, fst, snd) << " ";
    }
  }
  std::cout << std::endl;
}