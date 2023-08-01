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

if (WIN32 OR WIN64)
    add_custom_command(
            TARGET Tests POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:Tests>"
            COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:Tests> $<TARGET_RUNTIME_DLLS:Tests>
            COMMAND_EXPAND_LISTS
            VERBATIM
    )
endif()