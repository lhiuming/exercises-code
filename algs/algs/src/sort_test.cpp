// test the sorting algorithms
#include "sort.h"
#include "stdio.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

int main()
{
  // test exch() and is_sorted()
  vector<int> a;
  for (int i = 0; i < 5; i++) a.push_back(i);
  cout << "-- exch() and is_sorted() --" << endl;
  cout << "original:\t";
  algs::print_ints(a);
  cout << "sorted? " << algs::is_sorted(a) << endl;
  cout << "exchanged:\t";
  algs::exch(a, 2, 0);
  algs::print_ints(a);
  cout << "sorted? " << algs::is_sorted(a) << endl;

  // test sorting
  cout << "-- sorting --" << endl;
  vector<int> r = algs::read_ints();
  cout << "original: ";
  algs::print_ints(r);
  cout << "sorted? ";
  cout << algs::is_sorted(r) << endl;
  cout << "sorted? ";
  algs::selection_sort(r);
  cout << algs::is_sorted(r) << endl;

  return 0;
}
