#ifndef ALGS_STRINGS_STRING_SORT_HPP
#define ALGS_STRINGS_STRING_SORT_HPP

#include <limits>
#include <vector>
#include <iterator>
#include <iostream>
#include <stdexcept>

#include "../utils/misc.hpp"

/*
 * LSD string sort (radix sort).
 */

namespace algs {

// Helper. Get difference of integer
template<class Int>
inline std::size_t safe_sub(Int a, Int b)
{ return std::intmax_t(a) - b; }


// Least-significant-digit (LSD) first string sort. Actually accept any type
// That has operator[] and returns char-type
template<class RandomIt>
void lsd_string_sort(RandomIt beg, RandomIt end, std::size_t digits)
{
  // Static check for the value type
  using StringType = meta::IterValue<RandomIt>;
  static_assert( meta::IsString<StringType>::value,
    "Only support string-like type : ");

  // Type informations
  using Integral = typename std::remove_reference<
    decltype(std::declval<meta::IterValue<RandomIt>>()[0])
  >::type;
  constexpr Integral base = std::numeric_limits<Integral>::lowest();
  constexpr std::size_t u_max = std::numeric_limits<Integral>::max() - base;

  // We assume the radix is small
  static_assert( u_max <= std::numeric_limits<std::size_t>::max(),
    "Man, Integral type is just impossibly long.");
  static_assert( u_max < 65536, "Man, Integral type is too long.");
  constexpr std::size_t radix = u_max + 1;

  // First pass to make sure all string has at-least m chars
  for (auto iter = beg; iter != end; ++iter)
    if (iter->size() < digits) throw std::runtime_error("Not enough chars");

  // Run radix_sort
  std::size_t len = std::distance(beg, end);
  if (len < 2) return;
  std::vector<StringType> aux(len);
  for (std::size_t d = 0; d < digits; ++d)
  {
    const std::size_t cid = digits - d - 1;
    std::vector<std::size_t> count(radix + 1, 0);

    for (auto iter = beg; iter != end; ++iter) { // counting
      std::size_t index = safe_sub((*iter)[cid], base);
      ++count[index + 1];
    }
    for (int r = 0; r < radix; ++r) // make indices
      count[r + 1] += count[r];
    for (auto iter = beg; iter != end; ++iter) // partial sort (move)
      aux[ count[safe_sub((*iter)[cid], base)]++ ] = std::move(*iter);
    auto iter = beg;
    for (size_t i = 0; i < len; ++i) // move back
      *(iter++) = std::move(aux[i]);
  }

  return ;
}


} // namespace algs

#endif
