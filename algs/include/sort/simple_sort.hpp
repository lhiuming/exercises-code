#ifndef ALGS_SIMPLE_SORT_H
#define ALGS_SIMPLE_SORT_H

#include <functional>
#include <iterator>
#include <iostream> // DEBUG

/*
 * Insertion sort, Selection sort, and Shellsort.
 */

namespace algs {

// Selection sort /////////////////////////////////////////////////////////////

template<class ForwardIt, class Compare>
void selection_sort(ForwardIt beg, ForwardIt end, Compare less)
{
  for (; beg != end; ++beg) {
    // selection the minimum from [beg, end)
    ForwardIt min = beg;
    for (ForwardIt i = beg; i != end; ++i)
      if (less(*i, *min)) min = i;
    // put the minimum element at the start of [beg, end)
    using namespace std;
    swap(*beg, *min);
  }
}

template<class ForwardIt>
inline void selection_sort(const ForwardIt& beg, const ForwardIt& end)
{
  using value_type = typename std::iterator_traits<ForwardIt>::value_type;
  selection_sort(beg, end, std::less<value_type>());
}


// Insertion sort /////////////////////////////////////////////////////////////

template<class BidirectIt, class Compare>
void insertion_sort(BidirectIt beg, BidirectIt end, Compare less)
{
  // put *i at the correct position in [beg, i] by swapping backward
  for (BidirectIt i = (++beg)--; i != end; ++i) // skip i == beg
    for (BidirectIt j = i, _j = (--j)++; j != beg && less(*j, *_j); j = _j--) {
      using namespace std;
      swap(*j, *_j);
    }
}

template<class BidirectIt>
inline void insertion_sort(const BidirectIt& beg, const BidirectIt& end)
{
  using value_type = typename std::iterator_traits<BidirectIt>::value_type;
  insertion_sort(beg, end, std::less<value_type>());
}


// Shellsort //////////////////////////////////////////////////////////////////

template<class RandomIt, class Compare>
void shellsort(RandomIt beg, RandomIt end, Compare less)
{
  using index_t = typename std::iterator_traits<RandomIt>::difference_type;
  index_t n = end - beg;
  index_t h = 1;
  while (h < n / 3) h = 3 * h - 1; // an efficient sequence; see ALGS text
  while (h >= 1) {
    // using insertion-sorting to h-sort the sequence
    for (RandomIt i = beg + h; i != end; ++i)
      for (RandomIt j = i; (j - beg) >= h && less(*j, *(j - h)); j -= h) {
        using namespace std;
        swap(*j, *(j - h));
      }
    h = (h + 1) / 3; // update
  } // end while 
}

template<class RandomIt>
inline void shellsort(const RandomIt& beg, const RandomIt& end)
{
  using value_type = typename std::iterator_traits<RandomIt>::value_type;
  shellsort(beg, end, std::less<value_type>());
}


} // namespace algs

#endif
