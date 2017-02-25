// Exercise 7.15 (p266)
// writting constructors

#include "e7.4_5_person.h"

#include <string>
#include <iostream>

using namespace std;

Person::Person(istream& is) { // members are default initialized
  is >> name >> address;
}

Person::Person(string n, string add) : name(n), address(add) {};
