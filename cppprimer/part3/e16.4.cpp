// Exercise 16.4 (p658)
// write a template find function

#include <vector>
#include <string>
#include <list>
#include <iostream>

// don't usind namespace std, to prevent being ambiguous with std::find
// -> didn't work. I should use ::find
using std::cout; using std::endl;
using std::vector;
using std::string;
using std::list;

template <typename fwdIter, typename V>
fwdIter find(fwdIter b, fwdIter e, V target){
  while (b != e && target != *b) ++b;
  return b;
}

int main()
{
  // find vector
  vector<int> vi = {1, 2 , 5, 3, 2, 3, 9, 9, 2, 3};
  auto i = ::find(vi.begin(), vi.end(), 3);
  cout << *i << endl; // should be 3

  // find list of strings
  list<string> ls = { "fun", "jack", "study", "fun", "jacky"};
  auto j = ::find(ls.begin(), ls.end(), string("jacky"));
  cout << *j << endl; // should be jacky

  // if miss
  auto k = ::find(vi.begin(), vi.end(), 30);
  cout << *k << endl; // should be undifined

  return 0;
}
