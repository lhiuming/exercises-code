// Test reandom.h library
#include <iostream>
#include <vector>

#include <utils/random.hpp>
#include <utils/io.hpp>

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

  vector<int> v;
  Random::uniform(v, 10, 5);
  cout << "Make a vetor of random ints: " << v << endl;

  vector<double> u;
  Random::uniform(u, 5);
  cout << "Make a vector of random doubles: " << u << endl;

  return 0;
}
