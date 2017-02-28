// Exercise 13.5 (p399) and 13.8 (p501)
// writing a proper copy constructor and copy-assignment operator

#include <string>

class HasPtr {
public:
  HasPtr(const std::string &s = std::string()):
    ps(new std::string(s)), i(0) {}
  // the copy constructor
  HasPtr(const HasPtr &rhs):
    ps(new std::string(*rhs.ps)), i(rhs.i) {}
  // the copy-assignment operator
  HasPtr &operator=(const HasPtr& rhs) {
    // may be I should free the old ps first ? see chapter 12 first 
    delete ps; // yes, I should delete before allocate a new space
    ps = new std::string(*rhs.ps);
    i = rhs.i;
    return *this;
  }
private:
  std::string *ps;
  int i;
}
