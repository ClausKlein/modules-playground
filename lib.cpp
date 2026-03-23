module;

#include "legacy.hpp"

#ifdef PLAY_HAS_IMPORT_STD
import std;
#else
#include <array>
#include <tuple>
#endif

export module mylib;

export namespace mylib {

using mylib::Result;
using mylib::get;
using mylib::conv;

inline void dont_discard_result(std::array<int, std::tuple_size_v<Result>>) {}

}
