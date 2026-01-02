#ifndef TINYSTL_ITERATOR_H
#define TINYSTL_ITERATOR_H

#include <cstddef>
#include <type_traits>

#include "type_traits.h"

# define USING_STD_ITERATOR_TAG
namespace tinystl {
#ifdef USING_STD_ITERATOR_TAG
    using input_iterator_tag = std::input_iterator_tag;
    using output_iterator_tag = std::output_iterator_tag;
    using forward_iterator_tag = std::forward_iterator_tag;
    using bidirectional_iterator_tag = std::bidirectional_iterator_tag;
    using random_access_iterator_tag = std::random_access_iterator_tag;
#else
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : input_iterator_tag {};
    struct bidirectional_iterator_tag : forward_iterator_tag {};
    struct random_access_iterator_tag : bidirectional_iterator_tag {};
#endif


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
    struct has_iterator_category_of<Iterator, Category, typename enable_if<std::is_convertible<typename iterator_traits<
        Iterator>::iterator_category, Category>::value>::type > : true_type {
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
    struct is_iterator: bool_constant<is_output_iterator<Iterator>::value || is_input_iterator<Iterator>::value> {};

    // 原生指针的 Partial Specialization
    template<typename T>
    struct iterator_traits<T*> {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef ptrdiff_t difference_type;
    };

    template<typename T>
    struct iterator_traits<const T*> {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef ptrdiff_t difference_type;
    };

    template<typename Iterator>
    auto trait_category(const Iterator&) {
        typedef typename iterator_traits<Iterator>::iterator_category Category;  // 是空类
        return Category{};
    }

    template<typename Iterator>
    auto trait_distance(const Iterator&) {
        // 只使用类型，不创建值（可能没有构造），不是空类
        return static_cast<typename iterator_traits<Iterator>::difference_type*>(nullptr);
    }

    template<typename Iterator>
    auto trait_value_type(const Iterator&) {
        return static_cast<typename iterator_traits<Iterator>::value_type*>(nullptr);
    }

    /*
     *  distance
    */

    template<typename InputIterator>
    typename InputIterator::difference_type distance_dispatch(InputIterator first, InputIterator last, input_iterator_tag) {
        typename InputIterator::difference_type  n = 0;
        while (first != last) {
            ++first;
            ++n;
        }
        return n;
    };

    template<typename RandomIterator>
    typename RandomIterator::difference_type distance_dispatch(RandomIterator first, RandomIterator last, random_access_iterator_tag) {
        return last - first;
    };

    template<typename Iterator>
    typename Iterator::difference_type distance(Iterator first, Iterator last) {
        return distance_dispatch(first, last, trait_category(first));
    }

    /*
     *  advance
    */

    template<typename InputIterator, typename Distance>
    void advance_dispatch(InputIterator& it, Distance n, input_iterator_tag) {
        while (n > 0) {
            n--;
            ++it;
        }
    }

    template<typename BidirectionalIterator, typename Distance>
    void advance_dispatch(BidirectionalIterator& it, Distance n, bidirectional_iterator_tag) {
        if (n >= 0)
            ++it;
        else
            --it;
    }

    template<typename RandomIterator, typename Distance>
    void advance_dispatch(RandomIterator& it, Distance n, random_access_iterator_tag) {
        it += n;
    }

    template<typename Iterator, typename Distance>
    void advance(Iterator& it, Distance n) {
        return advance_dispatch(it, n, trait_category(it));
    }

    /*
     *  reverse_iterator
    */

    template<typename Iterator>
    class reverse_iterator {
    public:
        // 不能这样 typedef typename Iterator::iterator_category   iterator_category;
        // 因为 Iterator 可能是原生指针，没有这些类型成员
        typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
        typedef typename iterator_traits<Iterator>::value_type          value_type;
        typedef typename iterator_traits<Iterator>::pointer             pointer;
        typedef typename iterator_traits<Iterator>::reference           reference;
        typedef typename iterator_traits<Iterator>::difference_type     difference_type;

        typedef Iterator                      iterator_type;
        typedef reverse_iterator<Iterator>    self;

    public:
        reverse_iterator() = default;
        explicit reverse_iterator(iterator_type it): cur_{it} { }
        reverse_iterator(const self& rhs) = default;

        iterator_type base() const {
            return cur_;
        }
        reference operator*() const {
            iterator_type tmp = cur_;
            return *--tmp;
        }
        pointer operator->() const {
            return &(operator*());
        }
        self& operator++() {
            --cur_;
            return *this;
        }
        self operator++(int) {
            self tmp(*this);
            --cur_;
            return tmp;
        }
        self& operator--() {
            ++cur_;
            return *this;
        }
        self operator--(int) {
            self tmp(*this);
            ++cur_;
            return tmp;
        }
        self& operator+=(difference_type n) {
            cur_ -= n;
            return *this;
        }
        self& operator-=(difference_type n) {
            cur_ += n;
            return *this;
        }
        reference operator[](difference_type n) {
            return *(*this + n);
        }

    private:
        Iterator cur_;
    };

    template<typename Iterator>
    typename reverse_iterator<Iterator>::diffenence_type
        operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() - lhs.base();
    }

    template<typename Iterator>
    bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() == lhs.base();
    }

    template<typename Iterator>
    bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return !(lhs == rhs);
    }
    
    template<typename Iterator>
    bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return lhs.base() > rhs.base();
    }

    template<typename Iterator>
    bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs < lhs;
    }

    template<typename Iterator>
    bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return !(lhs > rhs);
    }

    template<typename Iterator>
    bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return !(lhs < rhs);
    }

}
#endif //TINYSTL_ITERATOR_H
