#ifndef TINYSTL_CONSTRUCT_H
#define TINYSTL_CONSTRUCT_H
#include <memory>

#include "utility.h"

namespace tinystl {
    // 在某块内存中调用对象的构造函数
    template<typename T, typename... Args>
    void construct(T* ptr, Args&&... args) {
        ::new (static_cast<void*>(ptr)) T(forward<Args>(args)...);
    }

    // 调用对象的析构函数
    template <typename T>
    void destroy_at(T* ptr, std::false_type) {
        // do nothing
    }

    template <typename T>
    void destroy_at(T* ptr, std::true_type) {
        if (ptr)
            ptr->~T();
    }

    template <typename T>
    void destroy(T* ptr) {
        _destroy_at(ptr, !std::is_trivially_destructible<T>{});
    }

    template <typename ForwardIterator>
    void destroy(ForwardIterator first, ForwardIterator last, std::false_type) {
        // do nothing
    }

    template <typename ForwardIterator>
    void destroy(ForwardIterator first, ForwardIterator last, std::true_type) {
        for (ForwardIterator it = first; it != last; ++it) {
            destroy_at(std::addressof(*it));
        }
    }
    
    template <typename ForwardIterator>
    void destroy(ForwardIterator first, ForwardIterator last) {
        destroy(first, last, !std::is_trivially_destructible<
            typename std::iterator_traits<ForwardIterator>::value_type>{});
    }

}
#endif //TINYSTL_CONSTRUCT_H