#ifndef TINYSTL_UTILITY_H
#define TINYSTL_UTILITY_H
#include <type_traits>

namespace tinystl {

    template<typename T>
    typename std::remove_reference<T>::type&& move(T&& arg) noexcept {
        return static_cast<typename std::remove_reference<T>::type &&>(arg);
    }

    template<typename T>
    // std::remove_reference<T>& : 只接受作为左值的函数形参
    T&& forward(typename std::remove_reference<T>::type& arg) noexcept {
        // Forwarding Reference 中， T = A& 或者 T = A
        return static_cast<T&&>(arg);
    }

    template<typename T>
    T&& forward(typename std::remove_reference<T>::type&& arg) noexcept {
        // 禁止把一个右值作为左值转发，会破坏引用语义
        static_assert(!std::is_lvalue_reference<T>::value, "cannot forward an rvalue as an lvalue");
        return static_cast<T&&>(arg);
    }

}

#endif //TINYSTL_UTILITY_H