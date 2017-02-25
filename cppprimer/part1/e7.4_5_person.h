// Exercise 7.4 (p260)
// Writing a class.
// see also e7.9, e7.15

#include <string>
#include <iostream>

// Declare. May be I should use struct as this point
struct Person {
  // friends declaration for non-member functions
  friend std::istream &read(std::istream &is, Person &p);
public:
  // constructors, defined in e7.15.cpp
  Person() = default;
  Person(std::istream& is);
  Person(std::string name, std::string address);
  // operations
  std::string name() const { return name; }
  std::string address() const { return address; }
private:
  // data member
  std::string name, address;
}; // don't forget this ';'

// non-membef functions, defined in e7.9.cpp
std::istream &read(std::istream &is, Person &p);
std::ostream &print(std::ostream &os, const Person &p);
