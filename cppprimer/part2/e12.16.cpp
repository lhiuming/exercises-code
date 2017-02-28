// Exercise 12.16 (p472)
// see error messeage of copying and assigning unique_ptr
// @NOTE: this program is intented to be erratic

#include <memory>
using namespace std;
int main() {
  unique_ptr<int> p1;
  p1.reset(new int(100));

  // copying
  // unique_ptr<int> p2(p1);  // error, because copy constructor is private
  unique_ptr<int> p2(new int(42));

  // assigning
  p2 = p1;  // error, because operator= is private 

  return 0;
}
