#ifndef ALGS_SORTING_MERGESORT_HPP
#define ALGS_SORTING_MERGESORT_HPP

#include <vector> // axulairy memory
#include <functional> // default compare
#include <iterator> // traits

/*
 * Top-down Mergesort and Bottom-up Mergesort, as well as some merging
 * functions.
 *
 * TODO: a mystrous bug below (search for `TODO` and `algs`)
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
template<class ForwardIt, class Compare>
void inplace_merge(ForwardIt beg, ForwardIt mid, ForwardIt end, Compare less)
{
  // use vector as auxilary array
  using value_type = typename std::iterator_traits<ForwardIt>::value_type;
  std::vector<value_type> aux;
  for(ForwardIt i = beg; i != mid; ++i)
    aux.push_back(std::move(*i));
  // merge aux and the second sequence, using beg as output
  merge(aux.begin(), aux.end(), mid, end, beg, less);
}

template<class ForwardIt>
void inplace_merge(ForwardIt beg, ForwardIt mid, ForwardIt end)
{
  using value_type = typename std::iterator_traits<ForwardIt>::value_type;
  // TODO why ambiguous???
  algs::inplace_merge(beg, mid, end, std::less<value_type>());
}


// Mergesort //////////////////////////////////////////////////////////////////
// Top-down mergesort and Bottom-up Mergesort.
////

// Top-down Mergesort
template<class RandomIt, class Compare>
void topdown_mergesort(RandomIt beg, RandomIt end, Compare less)
{
  // check the input
  if (end - beg <= 1) return;
  // using inplace_merge
  RandomIt mid = beg + (end - beg) / 2;
  topdown_mergesort(beg, mid, less);
  topdown_mergesort(mid, end, less);
  // TODO: why ambiguous?
  algs::inplace_merge(beg, mid, end, less);
}

template<class RandomIt>
void topdown_mergesort(RandomIt beg, RandomIt end)
{
  using value_type = typename std::iterator_traits<RandomIt>::value_type;
  topdown_mergesort(beg, end, std::less<value_type>());
}

// Bottom-up Mergesort
template<class RandomIt, class Compare>
void bottomup_mergesort(RandomIt beg, RandomIt end, Compare less)
{
  using diff_type = typename std::iterator_traits<RandomIt>::difference_type;
  diff_type N = end - beg;
  for (diff_type sz = 1; sz < N; sz += sz) {  // do nothing if N <= 1
    diff_type lo = 0;
    for (RandomIt k = beg; lo < N - sz; lo += sz + sz, k += (sz + sz))
      algs::inplace_merge(
        k, k + sz, (lo + sz + sz < N) ? k + sz + sz : end, less);
  }
}

template<class RandomIt>
void bottomup_mergesort(RandomIt beg, RandomIt end)
{
  using value_type = typename std::iterator_traits<RandomIt>::value_type;
  bottomup_mergesort(beg, end, std::less<value_type>());
}

// Default mergesort : use topdown_mergesort
template<class RandomIt, class Compare>
inline void mergesort(RandomIt beg, RandomIt end, Compare less)
{
  topdown_mergesort(beg, end, less);
}

template<class RandomIt>
inline void mergesort(RandomIt beg, RandomIt end)
{
  topdown_mergesort(beg, end);
}

} // namespace algs

#endif
