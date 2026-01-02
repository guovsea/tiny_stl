cmake_minimum_required(VERSION 3.28)
project(tinystl)

option(BUILD_TESTS "Build test projects" ON)

set(CMAKE_CXX_STANDARD 11)

add_library(tinystl INTERFACE
    include/type_traits.h
    include/iterator.h
    include/stream_iterator.h
)
target_include_directories(tinystl INTERFACE include)
add_library(tinystl::tinystl ALIAS tinystl)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()