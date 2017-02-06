// source file for the median function
#include <algorithm>
#include <stdexcept>
#include <vector>

using std::domain_error;
using std::vector;
using std::sort;
using std::copy;

// compute the median of a vector<double>
// this would copy the entire argument vector. becouse not reference?
double median(vector<double> vec)
{
  typedef vector<double>::size_type vec_sz;
  vec_sz size = vec.size();
  if (size==0)
    throw domain_error("median of an empty vector");

  sort(vec.begin(), vec.end());
  vec_sz mid = size / 2;

  return size%2 == 0 ? (vec[mid] + vec[mid+1])/2 : vec[mid];
}

// iterator version: no need to copy the entire vector
// I fail. how to get the mid position? what is its type?
// How to sort the vector?
// new knowledge from chapter 10
template<class Iter, class V>
V median_gr(const Iter& a, const Iter& b)
{
  if (a == b)
    throw domain_error("median of an empty vector");

  V ret = *a;

  vector<V> cp;
  copy(a, b, std::back_inserter(cp));

  sort(cp.begin(), cp.end());
  typedef typename vector<V>::size_type vec_size;
  vec_size size = cp.size() / 2;
  vec_size mid = cp.size() / 2;

  ret = size % 2 == 0 ? (cp[mid] + cp[mid+1])/2 : cp[mid];

  return ret;

}
