#find_package(gtest COMPONENTS gtest main REQUIRED)
include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG    v1.17.0
)
message(STATUS "GTest found: ${gtest_SOURCE_DIR}")
FetchContent_MakeAvailable(gtest)

enable_testing()

add_executable(run_tests
        test_iterator.cpp)

target_include_directories(run_tests PRIVATE
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(run_tests PRIVATE
    gtest_main
    tinystl::tinystl
)