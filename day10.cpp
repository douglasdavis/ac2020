#include <iostream>
#include <vector>
#include <fstream>

template<typename T>
auto load_numbers(const char* fname, std::size_t reserve = 0) {
  std::ifstream f(fname, std::ios::in);
  std::vector<T> vals;
  if (reserve > 0) {
    vals.reserve(reserve);
  }
  T val;
  while (f >> val) {
    vals.push_back(val);
  }
  f.close();
  return vals;
}

int main(int argc, char *argv[]) {
  auto vals = load_numbers<int>("data/day10.dat", 128);
  return 0;
}
