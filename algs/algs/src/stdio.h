// partially implemented StdIn and StdOut library
#ifndef ALGS_SRC_STDIO_H
#define ALGS_SRC_STDIO_H

#include <iostream>
#include <vector>

namespace algs {

// generic reading function
template<class V>
void read_vector(std::vector<V>& ret) {
  V c;
  while (std::cin >> c)
    ret.push_back(c);
}

// reading integers
std::vector<int> read_ints();

// generic priting function
template<class V>
void print_vector(const std::vector<V>& s) {
  for (typename std::vector<V>::size_type i = 0;
    i != s.size(); ++i)
    std::cout << s[i] << std::endl;
}

// print integers vertically
void print_ints(const std::vector<int>&);

} // namespace algs

#endif
