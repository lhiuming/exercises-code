// page 256
#include "include/sort.hpp"
#include "include/stopwatch.hpp"
#include <string>
#include <iostream>

using namespace std;
using namespace algs;

template<class Comparable>
double time(string alg, Comparable a) {
  Stopwatch timer;
  if (alg == "Insertion") insertion_sort(a);
  else if (alg == "Selection") selection_sort(a);
  else
    cout << "No matching sorting algorithm: " << alg << endl;
  return timer.elapsedTime();
}

int main(int nargs, char **arglist) {
  vector<double> a;
  for (int i = 1000; i > 0; --i)
    a.push_back(i);
  cout << time("Insertion", a) << endl;

  return 0;
}
