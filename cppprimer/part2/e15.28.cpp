// Exercise 15.28 (p631)
// using vector of (derived) objects

#include "e15.27_Bulk_quote.hpp" // don't include "Quote.hpp"; we have not guard

#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
  vector<Quote> basket;

  basket.push_back(Bulk_quote("alice in wanderlant", 100, 2, 0.3));
  basket.push_back(Bulk_quote("breif introduction to mathematics", 50, 5, 0.2));

  float ret = 0;
  for (auto a : basket)
    ret += a.net_price(10);

  cout << "total price: " << ret << endl; // no disccount !
  return 0;
}
