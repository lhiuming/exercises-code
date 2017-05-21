#ifndef ALGS_SORTING_MERGESORT_HPP
#define ALGS_SORTING_MERGESORT_HPP

#include <vector> // axulairy memory
#include <functional> // default compare
#include <iterator> // traits

/*
 * Top-down Mergesort and Bottom-up Mergesort, as well as some merging
 * functions.
 *
 * TODO: a mystrous bug below (search for `TODO`)
 */

namespace algs {

// Utilities //////////////////////////////////////////////////////////////////
// some utilities function for implementing mergesorts.
////

// Merge two input into a output
template<class InputIt1, class InputIt2, class OutputIt, class Compare>
void merge(
  InputIt1 b1, InputIt1 e1,
  InputIt1 b2, InputIt1 e2,
  OutputIt out, Compare less)
{
  // merge the two sequences and put into beg
  while (b1 != e1 && b2 != e2)
  {
    if (less(*b2, *b1))
      *(out++) = std::move(*(b2++));
    else
      *(out++) = std::move(*(b1++));
  }
  // handle the unmerge parts
  while (b1 != e1) *(out++) = std::move(*(b1++));
  while (b2 != e2) *(out++) = std::move(*(b2++));
}

template<class InputIt1, class InputIt2, class OutputIt>
void merge(
  InputIt1 b1, InputIt1 e1,
  InputIt1 b2, InputIt1 e2,
  OutputIt out)
{
  using value_type = typename std::iterator_traits<InputIt1>::value_type;
  merge(b1, e1, b2, e2, out, std::less<value_type>());
}

// Inplace merge, using a std::vector as auxilary memory
template<class BidirIt, class Compare>
void inplace_merge(BidirIt beg, BidirIt mid, BidirIt end, Compare less)
{
  // use vector as auxilary array
  using value_type = typename std::iterator_traits<BidirIt>::value_type;
  std::vector<value_type> aux;
  for(BidirIt i = beg; i != mid; ++i)
    aux.push_back(std::move(*i));
  // merge aux and the second sequence, using beg as output
  merge(aux.begin(), aux.end(), mid, end, beg, less);
}

template<class BidirIt>
void inplace_merge(BidirIt beg, BidirIt mid, BidirIt end)
{
  using value_type = typename std::iterator_traits<BidirIt>::value_type;
  // TODO why ambiguous???
  algs::inplace_merge(beg, mid, end, std::less<value_type>());
}

// Mergesort //////////////////////////////////////////////////////////////////
////

// Top_down Mergesort
template<class RandomIt, class Compare>
void topdown_mergesort(RandomIt b, RandomIt e, Compare less)
{
  // check the input
  if ( b == e) return;
  RandomIt mid = b + (e - b) / 2;
}


} // namespace algs

#endif
