#ifndef ALGS_UTILS_MISC_HPP
#define ALGS_UTILS_MISC_HPP

#include <type_traits>
#include <algorithm>

/*
 * Small little things.
 */

namespace algs {

namespace meta {

// Metafunctions //

// Logical conjunction
// NOTE: C++17 has a STL version for this `std::conjunction` ... XD
template<class...> struct All : std::true_type { };
template<class B> struct All<B> : B { };
template<class B1, class... Bn> struct All<B1, Bn...>
: std::conditional<bool(B1::value), All<Bn...>, B1>::type {};

// SFINAE template overloading //

// dummy class
enum class Enabler {};

// std::enable_if wrapper
template <class... Condition>
using EnableIf =
  typename std::enable_if<All<Condition...>::value, Enabler>::type;


// Not realy metas //

template <class Iterator>
using IterValue = typename std::iterator_traits<Iterator>::value_type;


} // namespace algs::meta

} // namespace algs

#endif
