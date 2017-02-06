// page 256
#include "include/sort.hpp"
#include "include/stopwatch.hpp"
#include "include/stdrandom.hpp"
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;
using namespace algs;

/* use Stopwatch class to get the wall-clock running time of a
 * sorting algorithm, on the input array a.
 */
template<class Comparable>
double time(string alg, Comparable a) {
  Stopwatch timer;
  if (alg == "Insertion") insertion_sort(a);
  else if (alg == "Selection") selection_sort(a);
  else
    cout << "No matching sorting algorithm: " << alg << endl;
  return timer.elapsedTime();
}

/* using alg to sort t random arrays of length t
 */
double timeRandomInput(string alg, int n, int t) {
  double total = 0.0;
  vector<double> a(n); // fill zero
  for (int i = 0; i < t; ++i) {
    for (int j = 0; j < n; ++j)
      a[j] = StdRandom::uniform();
    total += time(alg, a);
  }
  return total;
}

int main(int argn, char **argv) {
  // read arguments
  if (argn < 4) {
    cout << "Arguments not enough." << endl;
    return -1;
  }
  string alg1(argv[1]), alg2(argv[2]);
  int n = atoi(argv[3]), t = atoi(argv[4]);

  // do the compare
  double t1 = timeRandomInput(alg1, n, t);
  double t2 = timeRandomInput(alg2, n, t);
  cout << "For " << n << " random Doubles" << endl;
  printf("  %s is %.1f times faster than %s\n",
    alg1.c_str(), t2/t1, alg2.c_str());

  return 0;
}
