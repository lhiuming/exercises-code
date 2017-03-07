// Exercise 15.16 (p611)
// more practice using interface

#include "e15.15_Disc_quote.hpp"
#include <string>

class Limited_disc_quote : public Disc_quote {
public:
  // constructors
  Limited_disc_quote() = default;
  Limited_disc_quote(const std::string &bn, double price,
    std::size_t qty, std::size_t qty_max, double disc) :
    Disc_quote(bn, price, qty, disc), quantity_max(qty_max) { }
  // override the virtual function; also make it final
  double net_price(std::size_t purchase) const override final;
private:
  std::size_t quantity_max = 0;
};

double
Limited_disc_quote::net_price(std::size_t purchase) const
{
  if (purchase > quantity)
    if (purchase <= quantity_max)
      return purchase * price * (1 - discount);
    else
      return price * ( quantity * (1 - discount) + (quantity_max - purchase) );
  else
    return purchase * price;
}
