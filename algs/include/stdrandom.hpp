#ifndef ALGS_STDRANDOM_H
#define ALGS_STDRANDOM_H

#include <random>
#include <iostream>

namespace algs {

class StdRandom {
public:
  // uniform distributions
  static int uniform(int n) {
    if (n < 0) std::cout << "n must be positive." << std::endl;
    std::uniform_int_distribution<int> dist(0, n);
    return dist(generator);
  }
  static double uniform() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(generator);
  }
  // higher-order functions
  static void uniform(std::vector<double>& a) {
    for (std::vector<double>::size_type i = 0; i < a.size(); ++i)
      a[i] = uniform();
  }
  static void uniform(std::vector<int>& a, int r) {
    for (std::vector<int>::size_type i = 0; i < a.size(); ++i)
      a[i] = uniform(r);
  }
private:
  // no instantiation
  StdRandom() {}
  // the random generator
  // @todo: it this the correct waty to hold a static private?
  static std::default_random_engine generator;

};

// initialization
std::default_random_engine StdRandom::generator;

} // namespace algs

#endif
