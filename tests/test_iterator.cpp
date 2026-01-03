#include <vector>
#include <list>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <gtest/gtest.h>

#include "iterator.h"
#include "stream_iterator.h"


TEST(iterator, has_iterator_category) {
    struct A {
        typedef tinystl::input_iterator_tag    iterator_category;
    };
    EXPECT_TRUE(tinystl::has_iterator_category<A>::value);
    struct B {
    };
    EXPECT_FALSE(tinystl::has_iterator_category<B>::value);
}

TEST(iterator, iterator_traits) {
#ifdef USING_STD_ITERATOR_TAG
    EXPECT_TRUE(tinystl::is_input_iterator<std::istream_iterator<int>>::value);
    EXPECT_TRUE(tinystl::is_output_iterator<std::ostream_iterator<int>>::value);

    EXPECT_TRUE(tinystl::is_random_access_iterator<std::vector<int>::iterator>::value);
    EXPECT_FALSE(tinystl::is_bidirectional_iterator<std::forward_list<int>::iterator>::value);

    EXPECT_TRUE(tinystl::is_bidirectional_iterator<std::list<int>::iterator>::value);

    EXPECT_TRUE((tinystl::is_bidirectional_iterator<std::map<int, int>::iterator>::value));
    EXPECT_TRUE((!tinystl::is_random_access_iterator<std::map<int, int>::iterator>::value));
    EXPECT_TRUE((tinystl::is_forward_iterator<std::unordered_map<int, int>::iterator>::value));

    EXPECT_TRUE((tinystl::is_bidirectional_iterator<std::set<int>::iterator>::value));

    EXPECT_TRUE((tinystl::is_forward_iterator<std::unordered_set<int>::iterator>::value));
#endif
    struct A {

    };
    EXPECT_TRUE(tinystl::is_input_iterator<tinystl::istream_iterator<int>>::value);
    EXPECT_FALSE(tinystl::is_iterator<A>::value);
    EXPECT_TRUE(tinystl::is_iterator<tinystl::istream_iterator<int>>::value);

}

TEST(iterator, istream_iterator) {
    std::istringstream is{"1 2 3 4"};
    tinystl::istream_iterator<int> it{is};
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(*++it, 2);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it, 3);
    EXPECT_NE(it, tinystl::istream_iterator<int>{});
    ++it;
    auto tmp = it;
    EXPECT_EQ(*tmp, 4);
    ++it;
    EXPECT_EQ(it, tinystl::istream_iterator<int>{});
}

TEST(iterator, functions) {
    std::istringstream is{"1 2 3 4"};
    tinystl::istream_iterator<int> it{is};
    tinystl::advance(it, 1);
    EXPECT_EQ(*it, 2);

    std::istringstream is1{"1 2 3 4"};
    tinystl::istream_iterator<int> first{is1};
    auto distance = tinystl::distance(first, tinystl::istream_iterator<int>{});
    EXPECT_EQ(distance, 4);
}