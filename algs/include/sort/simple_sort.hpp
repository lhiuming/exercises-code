#ifndef ALGS_SIMPLE_SORT_H
#define ALGS_SIMPLE_SORT_H

#include <functional>
#include <iterator>
#include <iostream> // DEBUG

/*
 * Insertion sort, Selection sort, and Shellsort.
 */

namespace algs {

// Selection sort with custumized less-compare object
template<class ForwardIt, class Compare>
void selection_sort(ForwardIt beg, ForwardIt end, Compare less)
{
  for (; beg != end; ++beg) {
    ForwardIt min = beg;
    for (ForwardIt i = beg; i != end; ++i)
      if (less(*i, *min)) min = i;
    std::swap(*beg, *min);
  }
}

// Selection sort with default less-compare
template<class ForwardIt>
inline void selection_sort(ForwardIt beg, ForwardIt end)
{
  using value_type = typename std::iterator_traits<ForwardIt>::value_type;
  selection_sort(beg, end, std::less<value_type>());
}

} // namespace algs

#endif
