cmake_minimum_required(VERSION 3.23)

enable_testing()

project(Tests)

include(GoogleTest)

add_executable(TestCode test1.cpp)
target_link_libraries(TestCode PRIVATE GTest::gtest_main SDL2::SDL2main SDL2::SDL2 PUBLIC Code)

gtest_discover_tests(TestCode)