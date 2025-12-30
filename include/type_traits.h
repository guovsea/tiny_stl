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
}

#endif //TINYSTL_TYPE_TRAITS_H