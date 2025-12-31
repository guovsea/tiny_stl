#include <vector>
#include <list>
#include <forward_list>
#include "iterator.h"
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