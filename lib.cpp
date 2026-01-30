
module;

#include "legacy.hpp"
#include <array>
#include <tuple>

export module mylib;

export namespace mylib {

using mylib::Result;
using mylib::get;
using mylib::conv;

inline void dont_discard_result(std::array<int, std::tuple_size_v<Result>>) {}

}
