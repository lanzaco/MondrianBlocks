cmake_minimum_required(VERSION 3.25)
set(PROJECT_NAME TestProject)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
        SDL2
        URL     https://codeload.github.com/libsdl-org/SDL/zip/refs/tags/release-2.28.1
)
FetchContent_MakeAvailable(SDL2)

set(
        SourceFiles
        src/main.cpp
)

set(
        HeaderFiles
)

add_executable(${PROJECT_NAME} ${SourceFiles} ${HeaderFiles})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2)

if (WIN32 OR WIN64)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            VERBATIM
    )
endif()