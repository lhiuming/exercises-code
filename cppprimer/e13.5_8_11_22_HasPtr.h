// Exercise 13.5 (p399), 13.8 (p501), 13.11 (p504) and 13.22 (p511)
// writing a proper value-like class

#include <string>

class HasPtr {
public:
  HasPtr(const std::string &s = std::string()):
    ps(new std::string(s)), i(0) {}

  // the copy constructor
  HasPtr(const HasPtr &rhs):
    ps(new std::string(*rhs.ps)), i(rhs.i) {}

  // the copy-assignment operator; it is self-assignment safe 
  HasPtr &operator=(const HasPtr& rhs) {
    auto newp = new std::string(*rhs.ps); // create new before delete,
    delete ps;                            // to make self-assignment
    ps = newp;                            // safe !!!
    i = rhs.i;
    return *this;
  }

  // destructor
  ~HasPtr() {
    delete ps; // free the memory
    // following this, members are destroied automatically
  }

private:
  std::string *ps;
  int i;

};
