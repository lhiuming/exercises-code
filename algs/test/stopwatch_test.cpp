// test the timer class
#include "stopwatch.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
int main() {
  algs::Stopwatch timer;
  int i, sum;
  for (i = 1; i < 10000000; ++i)
    sum += std::pow(i, 0.1);
  cout << sum << " (" << timer.elapsedTime() << " secs)"<< endl;
  return 0;
}
