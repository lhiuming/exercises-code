// Implement a natural mergesort for linked list.

// Solution:
//    See include/fudamentals/list.hpp.
//    Linked list mergesort is Implemented by List::sort() and a private helper
// member List::split().

#include <iostream>

#include <fundamentals.hpp>
#include <utils.hpp>

int main()
{
  algs::List<int> list;
  std::vector<int> ran;
  algs::Random::uniform(ran, 99, 10);
  for (double d : ran) list.push_front(d);

  std::cout << "original list: " << list << std::endl;
  list.sort();
  std::cout << "sorted list:   " << list << std::endl;

  return 0;
}
