#ifndef ALGS_SORTING_LINEAR_SORT_HPP
#define ALGS_SORTING_LINEAR_SORT_HPP

#include <limits>
#include <iterator>
#include <cmath>

#include "../utils/misc.hpp" // SFINAE

/*
 * Radix sort (based on index-counting) for integral types (std::is_integral).
 */

namespace algs {

// Raidx sort based on index-counting. Only appliable to Integral type.
template<
  class RandomIt,
  meta::EnableIf< std::is_integral<meta::IterValue<RandomIt>> >...
> void radix_sort(RandomIt beg, RandomIt end)
{
  // Some alias
  using Integral = meta::IterValue<RandomIt>;
  constexpr int digits = std::numeric_limits<Integral>::digits; // as binary!
  constexpr int radix = std::numeric_limits<Integral>::radix; // should be 2
  auto len = std::distance(beg, end);

  // use binary radix
  static_assert(radix == 2, "Require bit implementation of interger");

  std::vector<Integral> aux(len);
  // Do index-counting on each digit (except sign-bit)
  for (int d = 0; d < digits; ++d) {
    std::vector<size_t> count(radix + 1, 0);
    for (auto iter = beg; iter != end; ++iter) // counting
      ++count[ (((*iter)>>d) & 1) + 1 ];
    for (int r = 0; r < radix; ++r) // make indices
      count[r + 1] += count[r];
    for (auto iter = beg; iter != end; ++iter) // partial sort
      aux[count[((*iter)>>d) & 1]++] = *iter;
    auto iter = beg;
    for (size_t i = 0; i < len; ++i) // copy back
      *(iter++) = aux[i];
  }
  if (std::is_signed<Integral>::value)
  {
    auto iter = beg;
    // first pass for negatives
    for (size_t i = 0; i < len; ++i) // first pass for negatives
      if (aux[i] < 0) *(iter++) = aux[i];
    // first pass for negatives
    for (size_t i = 0; i < len; ++i) // second pass for non-negatives
      if (aux[i] >= 0) *(iter++) = aux[i];
  }
} // end radix_sort


} // namespace algs

#endif
