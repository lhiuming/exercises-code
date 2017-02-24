// Exercise 6.54 (p250)
// writing return type of function pointer

#include <vector>

// declare a function that takes two int parameters and return an int
int ifuncii(int, int) { return 1; }

using fp_type = decltype(&ifuncii);
std::vector<fp_type> v1;   // vector holding pointer to above function
std::vector<int (*)(int, int)> v2; // equivalent 

int main() { // let the complier verify the solution
  v2.push_back(&ifuncii);
  v1.push_back(&ifuncii);

  return 0;
}
