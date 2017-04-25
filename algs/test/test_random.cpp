// Test reandom.h library
#include <iostream>
#include <vector>

#include <utils/random.hpp>

using namespace std;
using namespace algs;

int main()
{
  cout << "Make 7 random ints from [0, 5]:";
  for (int i = 0; i < 6; ++i)
  {
    cout << Random::uniform(10) << ", ";
  }
  cout << Random::uniform(10) << endl;

  cout << "Make 7 random doubles from U(0, 1):";
  for (int i = 0; i < 6; ++i)
  {
    cout << Random::uniform() << ", ";
  }
  cout << Random::uniform() << endl;

  return 0;
}
