// Exercise 6.47 (p243)
// using debugging preprocessor variables

#include <vector>
#include <iostream>

using namespace std;

void print(vector<int>::iterator beg, vector<int>::iterator end)
{
  if (beg == end) {
    cout << endl;
  } else {
    cout << *beg++ << ' ';
    #ifndef NDEBUF
    cout << ":: remaining: " << end - beg << endl;
    #endif
    print(beg, end);
  }
}

int main()
{
  vector<int> vi = {1, 3, 2, 4, 7};
  print(vi.begin(), vi.end());
  return 0;
}
