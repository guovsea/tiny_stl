#include <vector>
#include <list>
#include <forward_list>
#include "iterator.h"
#include "stream_iterator.h"
#include "gtest/gtest.h"


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
    // 无法萃取标准库
    // EXPECT_TRUE(tinystl::is_input_iterator<std::vector<int>>::value);
    // EXPECT_TRUE(tinystl::is_output_iterator<std::vector<int>>::value);

    // EXPECT_TRUE(tinystl::is_random_access_iterator<std::vector<int>>::value);
    // EXPECT_TRUE(!tinystl::is_random_access_iterator<std::list<int>>::value);

    // EXPECT_TRUE(tinystl::is_bidirectional_iterator<std::forward_list<int>>::value);
    // EXPECT_FALSE(tinystl::is_bidirectional_iterator<std::list<int>>::value);

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