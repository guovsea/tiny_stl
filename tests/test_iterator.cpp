#include "iterator.h"
#include "gtest/gtest.h"

TEST(iterator, iterator) {
    struct A {
        typedef tinystl::input_iterator_tag    iterator_category;
    };
    EXPECT_TRUE(tinystl::has_iterator_category<A>::value);
    struct B {
    };
    EXPECT_FALSE(tinystl::has_iterator_category<B>::value);

}