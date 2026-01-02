#ifndef TINYSTL_TYPE_TRAITS_H
#define TINYSTL_TYPE_TRAITS_H

namespace tinystl {
    template <typename T, T v>
    struct integral_constant {
        static constexpr T value = v;
    };

    template <bool v>
        using bool_constant = integral_constant<bool, v>;

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template <typename...>
    using void_t = void;

    template <bool, typename T = void>
    struct enable_if : false_type {};

    template <typename T>
    struct enable_if<true, T> : true_type {
        typedef T type;
    };

}

#endif //TINYSTL_TYPE_TRAITS_H