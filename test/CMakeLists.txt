cmake_minimum_required(VERSION 3.23)

enable_testing()

project(Tests)

include(GoogleTest)

add_executable(Tests
        test1.cpp testGameClass.cpp testBlockClass.cpp testFileHandlerClass.cpp testGridClass.cpp testSolverClass.cpp
        )
target_link_libraries(Tests PRIVATE GTest::gtest_main SDL2::SDL2main SDL2::SDL2 SDL2_ttf::SDL2_ttf-static PUBLIC Code)

ADD_TEST(
        NAME Tests
        COMMAND Tests
)