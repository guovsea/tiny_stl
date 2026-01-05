#ifndef TINYSTL_ALLOCATOR_H
#define TINYSTL_ALLOCATOR_H

#include "construct.h"
namespace tinystl {
    template <typename T>
    class allocator {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = size_t;
        using deference_type = ptrdiff_t;

        static T* allocate();
        static T* allocate(size_t n);

        static void deallocate(T *ptr);
        static void deallocate(T *ptr, size_t n);

        static void construct(T*ptr);
        template<typename... Args>
        static void construct(T*ptr, Args&&... args);

        static void destroy(T* ptr);
        static void destroy(T* first, T* last);
    };

    template<typename T>
    T * allocator<T>::allocate() {
        return static_cast<T*>(::operator new(sizeof(T)));
    }

    template<typename T>
    T * allocator<T>::allocate(size_t n) {
        return static_cast<T*>(::operator new(sizeof(T) * n));
    }


    template<typename T>
    void allocator<T>::deallocate(T *ptr) {
        if (ptr)
            ::operator delete(ptr);
    }

    template<typename T>
    void allocator<T>::deallocate(T *ptr, size_t n) {
        if (ptr)
            ::operator delete(ptr);
    }

    template<typename T>
    void allocator<T>::construct(T *ptr) {
        tinystl::construct(ptr);
    }

    template<typename T>
    template<typename ... Args>
    void allocator<T>::construct(T *ptr, Args &&...args) {
        tinystl::construct(ptr, args...);
    }

    template<typename T>
    void allocator<T>::destroy(T *ptr) {
        tinystl::destroy(ptr);
    }

    template<typename T>
    void allocator<T>::destroy(T *first, T *last) {
        tinystl::destroy(first, last);
    }
}

#endif //TINYSTL_ALLOCATOR_H