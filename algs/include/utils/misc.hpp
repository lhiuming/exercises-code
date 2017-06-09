#ifndef ALGS_UTILS_MISC_HPP
#define ALGS_UTILS_MISC_HPP

#include <type_traits>
#include <iterator>
#include <algorithm>

/*
 * Small little things.
 */

namespace algs {

namespace meta {

// Metafunctions //

// Logical ALL
// NOTE: C++17 has a STL version for this `std::conjunction` ... XD
template <class...> struct All : std::true_type { };
template <class B> struct All<B> : B { };
template <class B1, class... Bn> struct All<B1, Bn...>
: std::conditional<bool(B1::value), All<Bn...>, B1>::type {};

// Logical ANY
// NOTE: C++17 has `std::disjunction` ... :P
template<class...> struct Any : std::false_type { };
template<class B> struct Any<B> : B { };
template<class B1, class... Bn> struct Any<B1, Bn...>
: std::conditional<bool(B1::value), B1, Any<Bn...> >::type {};

// Check operator[]
template <class Indexable>
struct HasOperatorIndex {
private:
  // Check required function (by trying to call it)
  template<typename T>
  static constexpr auto check(T*) -> typename Any<
    std::is_same< decltype(std::declval<T>()[0]), std::true_type>,
    std::true_type>::type;
  // Default resolution
  template<typename>
  static constexpr std::false_type check(...);
public:
  using type = decltype(check<Indexable>(0));
  static constexpr bool value = type::value;
};

// Check string type : String[] -> Integer&
template <class StringLike>
using IsString = All<
  std::is_integral<typename
    std::remove_reference<decltype(std::declval<StringLike>()[0])>::type>,
  HasOperatorIndex<StringLike>
>;


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
