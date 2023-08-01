cmake_minimum_required(VERSION 3.23)

project(AbschlussProjekt)

set(CMAKE_CXX_STANDARD 23)


include(FetchContent)
FetchContent_Declare(
        SDL2
        URL     https://codeload.github.com/libsdl-org/SDL/zip/refs/tags/release-2.28.1
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
        googletest
        URL https://codeload.github.com/google/googletest/zip/refs/tags/v1.13.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
add_subdirectory(test)