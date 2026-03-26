module;  // global module fragment

#ifdef PLAY_HAS_IMPORT_STD
import std;
#else
# include <concepts>
# include <cstddef>
# include <string_view>
# include <tuple>
# include <type_traits>
# include <utility>
#endif

export module mylib;

export namespace mylib {

    class Result {
        int value_{};

      public:
        Result() = default;

        int& getValue() & {
            return value_;
        }
        [[nodiscard]] const int& getValue() const& {
            return value_;
        }
        int&& getValue() && {
            return std::move(value_);
        }
    };

    // ADL-based tuple interface
    // ADL stands for Argument-Dependent Lookup
    template <std::size_t I> int& get(Result& r) {
        static_assert(I == 0);
        return r.getValue();
    }

    template <std::size_t I> const int& get(const Result& r) {
        static_assert(I == 0);
        return r.getValue();
    }

    template <std::size_t I> int&& get(Result&& r) {
        static_assert(I == 0);
        return std::move(r).getValue();
    }

    template <class T>
        requires std::convertible_to<T, std::string_view>
    void conv(const T& /*unused*/) {}

}  // namespace mylib

// ---- std specializations MUST be visible to consumers ----
template <> struct std::tuple_size<mylib::Result> : std::integral_constant<std::size_t, 1U> {};

template <> struct std::tuple_element<0U, mylib::Result> {
    using type = int;
};
