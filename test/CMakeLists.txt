cmake_minimum_required(VERSION 3.23)

enable_testing()

project(Tests)

include(GoogleTest)

set(
        TestSources
        test1.cpp
        testBlockClass.cpp
        testFileHandlerClass.cpp
        testGridClass.cpp
        testSolverClass.cpp
)

set(
        assets
        ../src/data/data_file.txt
        ../src/data/empty_file.txt
        ../src/data/file_setsGridSizeTo_7.txt
)

add_executable(
        Tests
        ${TestSources}
)
target_link_libraries(Tests PRIVATE GTest::gtest_main GTest::gtest SDL2::SDL2-static SDL2::SDL2main SDL2_ttf::SDL2_ttf-static PUBLIC Code)

file(COPY ${assets} DESTINATION ${CMAKE_BINARY_DIR}/test)

ADD_TEST(
        NAME Tests
        COMMAND Tests
)