#include <iostream>

//#include "median.h"

using std::cout;
using std::endl;



#include <algorithm>
#include <stdexcept>
#include <vector>

using std::domain_error;
using std::vector;
using std::sort;
using std::copy;
template<class Iter, class V>
V median_gr(Iter a, Iter b)
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


int main()
{
  int data[] = {1100, 2, 5, 3, 6, 1, 9, 3};
  //cout << *data << endl;
  int ret = median_gr(data, data + 7);
  cout << ret << endl;

  return 0;
}
