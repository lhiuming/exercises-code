// Exercise 7.9 (p262)
// adding non-member operation for Person class. (see e7.4)

#include "e7.4_5_person.h"
#include <iostream>
#include <string>

using namespace std;

istream &read(istream &is, Person &p) // a friend function to Person 
{
  is >> Person.name >> Person.address;
  return is;
}

ostream &print(ostream &os, const Person &p)
{
  os << Person.name() << " : " << Person.address();
  return os;
}
