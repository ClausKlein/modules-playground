module;  // global module fragment

#include "legacy.hpp"  // attaged to global module fragment

#ifdef PLAY_HAS_IMPORT_STD
import std;
#else
# include <array>
# include <tuple>
#endif

export module mylib;  // start of module purview

export namespace mylib {  // part of module interface

    using mylib::conv;
    using mylib::get;
    using mylib::Result;

    inline void dont_discard_result(std::array<int, std::tuple_size_v<Result>>) {}

}  // namespace mylib
