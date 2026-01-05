#include <gtest/gtest.h>

#include "allocator.h"


TEST(allocator, construct_one) {
    static bool constructed = false;
    static bool destroyed = false;
    struct Foo {
        Foo() {
            constructed = true;
        }
        ~Foo() {
            destroyed = true;
        }
    };
    Foo* ptr = tinystl::allocator<Foo>::allocate();
    tinystl::allocator<Foo>::construct(ptr);
    tinystl::allocator<Foo>::destroy(ptr);
    EXPECT_TRUE(constructed);
    EXPECT_TRUE(destroyed);
}

TEST(allocator, construct_list) {
    static size_t constructed{};
    static size_t destroyed{};
    struct Foo {
        Foo() {
            ++constructed;
        }
        ~Foo() {
            ++destroyed;
        }
    };
    Foo* ptr = tinystl::allocator<Foo>::allocate(10);
    tinystl::allocator<Foo>::construct(ptr);
    tinystl::allocator<Foo>::destroy(ptr, ptr + 10);
    // 调用未构造的对象的析构函数是很危险的事情
    EXPECT_EQ(constructed, 1);
    EXPECT_EQ(destroyed, 10);
}

TEST(allocator, construct_with_arguments) {
    static bool constructed = false;
    static bool destroyed = false;
    struct Foo {
        Foo(int a, int b) : a_(a), b_(b){
            constructed = true;
        }
        ~Foo() {
            destroyed = true;
        }
        int a_{};
        int b_{};
    };
    Foo* ptr = tinystl::allocator<Foo>::allocate();
    tinystl::allocator<Foo>::construct(ptr, 42, 10);
    EXPECT_TRUE(constructed);
    tinystl::allocator<Foo>::destroy(ptr);
    EXPECT_EQ(ptr->a_, 42);
    EXPECT_EQ(ptr->b_, 10);
    EXPECT_TRUE(destroyed);
}

TEST(allocator, construct_with_obj) {
    static bool constructed = false;
    static bool destroyed = false;
    struct Foo {
        Foo(int a, int b) : a_(a), b_(b){
            constructed = true;
        }
        ~Foo() {
            destroyed = true;
        }
        int a_{};
        int b_{};
    };
    Foo* ptr = tinystl::allocator<Foo>::allocate();
    tinystl::allocator<Foo>::construct(ptr, Foo{42, 10});
    EXPECT_TRUE(constructed);
    tinystl::allocator<Foo>::destroy(ptr);
    EXPECT_EQ(ptr->a_, 42);
    EXPECT_EQ(ptr->b_, 10);
    EXPECT_TRUE(destroyed);
}