#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

int main()
{
  vector<int> u(10,100);
  vector<int> v;
  //copy(u.begin(), u.end(), v.begin());
  //copy(u.begin(), u.end(), back_inserter(v));
  copy(u.begin(), u.end(), inserter(v, v.begin()));


  vector<int>::iterator iter;
  for (iter = u.begin(); iter != u.end(); iter++)
    cout << *iter << ' ';
  cout << endl;
  for (iter = v.begin(); iter != v.end(); iter++)
    cout << *iter << ' ';
  cout << endl;

  return 0;
}
