cmake_minimum_required(VERSION 3.20)
project(RotatableGridVector)

set(CMAKE_CXX_STANDARD 20)

install(FILES RotatableGridVector.hpp DESTINATION include)

include(FetchContent)
FetchContent_Declare(
		googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
add_executable(RotatableGridVector_test RotatableGridVector_test.cpp)
target_link_libraries(RotatableGridVector_test GTest::gtest_main)
target_include_directories(RotatableGridVector_test PUBLIC GTEST_INCLUDE_DIRS)
gtest_discover_tests(RotatableGridVector_test)
