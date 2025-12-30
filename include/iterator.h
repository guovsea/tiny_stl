#ifndef TINYSTL_ITERATOR_H
#define TINYSTL_ITERATOR_H

#include <cstddef>
#include <type_traits>

#include "type_traits.h"

namespace tinystl {
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag {};
    struct bidirectional_iterator_tag {};
    struct random_access_iterator_tag {};

    // iterator 必须有这 5 种类型成员
    template<typename Category, typename T, typename Distance = std::ptrdiff_t,
        typename Pointer = T *, typename Reference = T &>
    struct iterator {
        typedef Category iterator_category;
        typedef T value_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Distance difference_type;
    };

    template<typename T, typename = void>
    struct has_iterator_category : false_type {
    };

    template<typename T>
    struct has_iterator_category<T, void_t<typename T::iterator_category> > : true_type {
    };

    template<typename Iterator, bool>
    struct iterator_traits_impl {
    };

    template<typename Iterator>
    struct iterator_traits_impl<Iterator, true> {
        // 萃取迭代器的特性
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::difference_type difference_type;
    };

    template<typename Iterator>
    struct iterator_traits : iterator_traits_impl<Iterator, has_iterator_category<Iterator>::value> {
    };

    template<typename Iterator, typename Category, typename = void>
    struct has_iterator_category_of : false_type {
    };

    template<typename Iterator, typename Category>
    struct has_iterator_category_of<Iterator, Category, std::enable_if<std::is_convertible<typename iterator_traits<
        Iterator>::iterator_category, Category>::value> > : true_type {
    };

    template<typename Iterator>
    struct is_input_iterator : has_iterator_category_of<Iterator, input_iterator_tag> {
    };

    template<typename Iterator>
    struct is_exactly_input_iterator : bool_constant<has_iterator_category_of<Iterator, input_iterator_tag>::value
        && !has_iterator_category<Iterator, forward_iterator_tag>::value> {
    };

    template<typename Iterator>
    struct is_output_iterator : has_iterator_category_of<Iterator, output_iterator_tag> {};

    template<typename Iterator>
    struct is_forward_iterator : has_iterator_category_of<Iterator, forward_iterator_tag> {};

    template<typename Iterator>
    struct is_bidirectional_iterator: has_iterator_category_of<Iterator, bidirectional_iterator_tag> {};

    template<typename Iterator>
    struct is_random_access_iterator: has_iterator_category_of<Iterator, random_access_iterator_tag> {};

    template<typename Iterator>
    struct is_iterator: bool_constant<is_output_iterator<Iterator>::value && is_input_iterator<Iterator>::value> {};

    // 指针的 Partial Specialization
    template<typename T>
    struct iterator_traits<T *> {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef ptrdiff_t difference_type;
    };
}
#endif //TINYSTL_ITERATOR_H
