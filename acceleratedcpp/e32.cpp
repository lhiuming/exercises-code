#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;

using std::vector;
using std::sort;

int main()
{
  cout << "Please enter a list of integers, "
    "end with EOF: ";
  
  vector<int> integers;
  int x;
  while (cin >> x)
    integers.push_back(x);

  sort(integers.begin(), integers.end());

  typedef vector<int>::size_type vec_sz;
  vec_sz size = integers.size();
  vector<vec_sz> breaks;
  for (vec_sz i = 0; i < 4; i++)
    breaks.push_back(size * i / 4);

  vector<vec_sz>::size_type  breaki = 0;
  for (vec_sz i = 0; i < size; i++) {
    if (i == breaks[breaki]) {
      breaki++;
      cout << endl;
    }
    cout << integers[i] << "\t";
  }
  cout << endl;

  return 0;
}
