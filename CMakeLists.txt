cmake_minimum_required(VERSION 3.23)

project(AbschlussProjekt)

set(CMAKE_CXX_STANDARD 23)

cmake_policy(SET CMP0135 NEW)

include(FetchContent)
FetchContent_Declare(
        SDL2
        URL     https://codeload.github.com/libsdl-org/SDL/zip/refs/tags/release-2.28.1
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
add_subdirectory(test)