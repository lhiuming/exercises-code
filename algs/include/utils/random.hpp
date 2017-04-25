#ifndef ALGS_STDRANDOM_H
#define ALGS_STDRANDOM_H

#include <random>
#include <iostream>

namespace algs {

class Random {
public:

  // uniform distributions
  static int uniform(int n) {
    if (n < 0) {
      std::cerr << "n must be positive." << std::endl;
      exit(1); }
    std::uniform_int_distribution<int> u_dist(0, n);
    return u_dist(get_generator());
  }
  static double uniform() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(get_generator());
  }

  // fill an vector with random values
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
  Random() = delete;

  // the random generator; place in a function to let it be initialized once
  static std::default_random_engine& get_generator() {
    static std::default_random_engine generator;
    return generator;
  }

};

} // namespace algs

#endif
