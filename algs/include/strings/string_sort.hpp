#ifndef ALGS_STRINGS_STRING_SORT_HPP
#define ALGS_STRINGS_STRING_SORT_HPP

#include <string>
#include <iostream>

#include "../utils/misc.hpp"

/*
 * LSD string sort (radix sort).
 */

namespace algs {

// Least-significant-digit (LSD) first string sort. Actually accept any type
// That has operator[] and returns char-type
template<class RandomIt>
void lsd_string_sort(RandomIt beg, RandomIt end)
{
  using StringType = meta::IterValue<RandomIt>;
  static_assert( meta::IsString<StringType>::value,
    "Only support string-like type : ");

  return ;
}


} // namespace algs

#endif
