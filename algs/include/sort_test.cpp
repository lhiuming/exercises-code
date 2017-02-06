// test the sorting algorithms
#include "sort.hpp"
#include "stdio.hpp"
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
  vector<int> inp = algs::read_ints();
  cout << "original: ";
  algs::print_ints(inp);
  // selection sort
  auto t = inp;
  cout << "selection sort:\t";
  algs::selection_sort(t);
  cout << algs::is_sorted(t) << endl;
  // insertion sort
  cout << "insertion sort:\t";
  t = inp;
  algs::insertion_sort(t);
  cout << algs::is_sorted(t) << endl;

  return 0;
}
