// test the sorting algorithms
#include "sort.hpp"
#include "stdrandom.hpp"
#include "stdio.hpp"
#include <vector>
#include <iostream>

using namespace algs;
using namespace std;

int main()
{
  // test exch() and is_sorted()
  vector<int> a;
  for (int i = 0; i < 5; i++) a.push_back(i);
  cout << "-- exch() and is_sorted() --" << endl;
  cout << "orig: ";
  algs::print_ints(a);
  cout << "sorted: " << algs::is_sorted(a) << endl;
  cout << "exch: ";
  algs::exch(a, 2, 0);
  algs::print_ints(a);
  cout << "sorted: " << algs::is_sorted(a) << endl;

  // test sorting
  // read input integer list
  cout << "-- sorting --" << endl;
  vector<int> rand_int(15);
  StdRandom::uniform(rand_int, 9);
  cout << "original: ";
  print_ints(rand_int);
  // selection sort
  vector<int> t = rand_int;
  cout << "selection sort:\t";
  selection_sort(t);
  cout << is_sorted(t) << endl;
  // insertion sort
  cout << "insertion sort:\t";
  t = rand_int;
  insertion_sort(t);
  cout << is_sorted(t) << endl;
  // shellsort
  cout << "shellort: \t";
  t = rand_int;
  shellsort(t);
  cout << is_sorted(t) << endl;

  return 0;
}
