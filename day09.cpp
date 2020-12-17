#include <algorithm>
#include <vector>
#include <numeric>
#include <cstdio>
#include <iostream>

std::vector<std::size_t> get_numbers(const char* fname) {
  std::FILE* f = std::fopen(fname, "r");
  std::size_t n;
  std::vector<std::size_t> v;
  v.reserve(1024);
  while (std::fscanf(f, "%ld\n", &n) == 1) {
    v.push_back(n);
  }
  std::fclose(f);
  return v;
}

int count_digits(std::size_t n) {
  int d = 0;
  while (n > 0) {
    n /= 10;
    d++;
  }
  return d;
}

auto sums(const std::vector<std::size_t>& v, std::size_t lo_b, std::size_t hi_b) {
  std::vector<std::size_t> s;
  for (std::size_t i = lo_b; i <= hi_b; ++i) {
    for (std::size_t j = lo_b; j <= hi_b; ++j) {
      if (v[i] != v[j]) {
        s.push_back(v[i] + v[j]);
      }
    }
  }
  return s;
}

auto get_p2_numbers(const std::vector<std::size_t>& v, std::size_t inval) {
  for (std::size_t i = 0; i < v.size(); ++i) {
    for (std::size_t j = (i+1); j < v.size(); ++j) {
      auto i1 = v.begin() + i;
      auto i2 = v.begin() + j;
      std::size_t sum = std::accumulate(i1, i2, 0);
      if (sum == inval) {
        return std::make_pair(i, j);
      }
    }
  }
  return std::make_pair<std::size_t, std::size_t>(0, 0);
}

int main() {
  auto v = get_numbers("data/day9.dat");
  auto total = v.size();
  std::size_t invalid_number = 0;
  for (std::size_t i = 25; i < total; ++i) {
    auto stc = sums(v, i - 25, i - 1);
    auto res = std::find(std::begin(stc), std::end(stc), v[i]);
    if (res == std::end(stc)) {
      invalid_number = v[i];
    }
  }
  std::cout << "Part 1: " << invalid_number << std::endl;

  int n_digits = count_digits(v.back());
  std::size_t chop_above = total - 1;
  while (n_digits > count_digits(invalid_number)) {
    n_digits = count_digits(v[chop_above]);
    chop_above--;
  }

  std::vector<std::size_t> v2(v.begin(), v.begin() + chop_above);
  auto [idx1, idx2] = get_p2_numbers(v2, invalid_number);
  auto min_value = *std::min_element(v2.begin() + idx1, v2.begin() + idx2);
  auto max_value = *std::max_element(v2.begin() + idx1, v2.begin() + idx2);

  std::cout << "Part 2: " << min_value + max_value << std::endl;

  return 0;
}
