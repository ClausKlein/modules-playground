
#include <concepts>
#include <cstddef>
#include <string_view>
#include <tuple>
#include <type_traits>

namespace mylib {
 
class Result {
  int value_ {};
public:
  Result() = default;
  int& getValue() & { return value_; }
  const int& getValue() const& { return value_; }
  int&& getValue() && { return std::move(value_); }
};

template <std::size_t I>
int& get(Result& r) { return r.getValue(); }

template <std::size_t I>
const int& get(const Result& r) { return r.getValue(); }

template <std::size_t I>
int&& get(Result&& r) { return std::move(r).getValue(); }

template <class T>
  requires std::convertible_to<T, std::string_view>
void conv(const T&) {}

}

template <>
struct std::tuple_size<mylib::Result> : std::integral_constant<std::size_t, 1u> {};

template <>
struct std::tuple_element<0u, mylib::Result>  { using type = int; };

