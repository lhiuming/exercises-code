#include <vector>
#include <array>
#include "StdIO.h"

using std::vector;

vector<int> histogram(vector<int> a, int M)
{
  vector<int> ret(M);
  for(vector<int>::size_type i = 0; i < a.size(); ++i)
    if(0 <= a[i] && a[i] < M) ret[a[i]]++;
  return ret;
}

int main()
{
  vector<int> get;
  StdIn::read(get);
  StdOut::print(get);

  vector<int> h = histogram(get, 10);
  StdOut::print(h);
  return 0;
}
