#ifdef PLAY_HAS_IMPORT_STD
import std;
#else
# include <iostream>
#endif

#ifdef __APPLE__
// not with g++ # include <cassert>    // assert
# include <cerrno>  // errno, all E* errno macros
# include <cfloat>  // floating-point limit/characteristic macros (same as C)
// not with g++ # include <cinttypes>  // format/scan macros (same as C)
# include <climits>  // integer limit macros (same as C)
# include <cstdarg>  // va_arg, va_copy, va_end, va_start
// not with g++ # include <cstdint>    // fixed-width limit and optional format macros (same as C)
# include <version>  // __cplusplus, __cpp_lib_*, __cpp_*, etc.
#endif

// /usr/local/Cellar/llvm/22.1.1/bin/../include/c++/v1/__type_traits/promote.h:38:7:
// error: type alias template redefinition with different types
// FIXME: #include <cmath>        // HUGE_VAL*, INFINITY, NAN, FP_*, MATH_*, math_errhandling

// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h:88:34: error: conflicting
// type for imported declaration '__pthread_rwlock_arch_t
// pthread_rwlock_t::__data'
// FIXME:

#ifdef __APPLE__
// not with g++ # include <clocale>  // LC_* and other C locale macros
# include <csetjmp>  // setjmp (and any other C macros from <setjmp.h>)
// not with g++ # include <csignal>  // SIG_* macros (same as C)
// not with g++ # include <cstddef>  // NULL, offsetof
// not with g++ # include <cstdlib>  // EXIT_SUCCESS, EXIT_FAILURE
// not with g++ # include <ctime>    // time/clocks macros (same as C)
#endif

int main() {
#if defined(__APPLE__) && defined(NULL)
    // use current time as seed for random generator
    std::srand(std::time(NULL));  // NOLINT

    std::cout << "RAND_MAX: " << RAND_MAX << '\n'
              << "INT_MAX: " << INT_MAX << '\n'
              << "INFINITY: " << INFINITY << '\n'
              << "Random value on [0,1]: "
              // NOLINTNEXTLINE
              << static_cast<double>(std::rand()) / RAND_MAX << '\n';
    return EXIT_SUCCESS;
#endif
}
