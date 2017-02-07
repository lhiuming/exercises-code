#ifndef ALGS_SORT_H
#define ALGS_SORT_H

#include <vector>

namespace algs {

using std::vector;

// utilities

template<class V>
void exch(vector<V>& a,
          typename vector<V>::size_type i,
          typename vector<V>::size_type j) {
  V tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

template<class Comparable>
bool is_sorted(vector<Comparable>& a) {
  if (a.size() < 2) return true;
  typedef typename vector<Comparable>::const_iterator iter_t;
  iter_t b = a.begin(), e = a.end();
  iter_t c = b + 1;
  while (c != e)
    if (*c < *b)
      return false;
    else
      b = c++;
  return true;
}

// sorting algorithms

template<class Comparable>
void selection_sort(vector<Comparable>& a) {
  typedef typename vector<Comparable>::size_type size_t;
  size_t n = a.size();
  for (size_t i = 0; i < n; i++) {
    size_t min = i;
    for (size_t j = i; j < n; j++)
      if (a[j] < a[min]) min = j;
    exch(a, i, min);
  }
}

template<class Comparable>
void insertion_sort(vector<Comparable>& a) {
  typedef typename vector<Comparable>::size_type size_t;
  size_t n = a.size();
  for (size_t i = 1; i < n; ++i)
    for (size_t j = i; j > 0 && a[j] < a[j-1]; --j)
      exch(a, j, j-1);
}

template<class Comparable>
void shellsort(vector<Comparable>& a) {
  using size_t = typename vector<Comparable>::size_type;
  size_t n = a.size();
  size_t h = 1;
  while (h < n / 3) h = 3 * h - 1; // an efficient sequence
  while (h >= 1) {
    // h sort the array, using insertion sort
    for (size_t i = h; i < n; i++) {
      for (size_t j = i; j >= h && a[j] < a[j-h]; j -= h)
        exch(a, j, j-h);
    }
    h = h / 3; // update
  }
}

} // namespace algs

#endif
