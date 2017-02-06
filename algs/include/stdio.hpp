// partially implemented StdIn and StdOut library
#ifndef ALGS_SRC_STDIO_H
#define ALGS_SRC_STDIO_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

namespace algs {

// generic reading function
template<class V>
void read_vector(std::vector<V>& ret) {
  V c;
  while (std::cin >> c)
    ret.push_back(c);
}

// reading integers
std::vector<int> read_ints() {
  std::vector<int> a;
  read_vector(a);
  return a;
}
// generic priting function
template<class V>
void print_vector(const std::vector<V>& s) {
  for (typename std::vector<V>::size_type i = 0;
    i != s.size(); ++i)
    std::cout << s[i] << std::endl;
}

// print integers vertically
void print_ints(const std::vector<int>& a) {
  typedef std::vector<int>::size_type size_t;
  for (size_t i = 0; i < a.size(); i++) {
    std::printf("%4d", a[i]);
  }
  std::cout << std::endl;
}

} // namespace algs

#endif
