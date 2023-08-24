cmake_minimum_required(VERSION 3.23)

project(MondrianBlocks)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 17)

include(FetchContent)

if (${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.24)
    cmake_policy(SET CMP0135 NEW)
endif ()

option(BUILD_SHARED_LIBS "" OFF)
option(BUILD_SAMPLES "" OFF)
option(SDL2MIXER_SAMPLES "" OFF)
option(SDL2MIXER_INSTALL "" OFF)
option(SDL2MIXER_VENDORED "" ON)
option(SDL2TTF_SAMPLES "" OFF)
option(SDL2TTF_INSTALL "" OFF)
option(SDL2TTF_VENDORED "" ON)
option(SDL_STATIC_PIC "" ON)
option(SUPPORT_OGG "" ON)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.28.2
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
    SDL2_ttf
    URL https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2.zip
)
FetchContent_MakeAvailable(SDL2_ttf)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
add_subdirectory(test)