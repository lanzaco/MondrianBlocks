cmake_minimum_required(VERSION 3.23)

enable_testing()

project(Tests)

include(GoogleTest)

add_executable(Tests test1.cpp)
target_link_libraries(Tests PRIVATE GTest::gtest_main SDL2::SDL2main SDL2::SDL2 PUBLIC Code)

ADD_TEST(
        NAME Tests
        COMMAND Tests
)


