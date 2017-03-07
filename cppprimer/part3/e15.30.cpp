// Exercise 15.30 (p634)
// wiriting vector of pointers of class hierachy

#include "e15.27_Bulk_quote.hpp" // don't include "Quote.hpp"; we have not guard
#include <vector>
#include <memory>

using namespace std;

// define the Basket class

class Basket {
public:
  // only test Bulk_quote insert
  void add_item(const Bulk_quote& sale) {
    basket.push_back(std::shared_ptr<Quote>(sale.clone())); }
  // iterate and sum up the total price; each book bought 10 times
  double total_receipt() const {
    double ret = 0;
    for (auto a : basket) ret += a->net_price(10);
    return ret;
  }
private:
  vector<std::shared_ptr<Quote>> basket;
};

#include <string>
#include <iostream>

int main() {
  Basket basket;

  basket.add_item(Bulk_quote("alice in wanderlant", 100, 2, 0.3));
  basket.add_item(Bulk_quote("breif introduction to mathematics", 50, 5, 0.2));

  cout << "total receipt by basket: " << basket.total_receipt() << endl;

  return 0;
}
