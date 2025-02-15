cmake_minimum_required(VERSION 3.23)

set(
        SourceFiles
        Grid.cpp
        Blocks.cpp
        Renderer.cpp
        Solver.cpp
        FileHandler.cpp
        Game.cpp
        UserInterface.cpp
        Difficulty.cpp
)

set(
        HeaderFiles
        Grid.hpp
        Blocks.hpp
        Solver.hpp
        Renderer.hpp
        Colors.hpp
        Defines.hpp
        FileHandler.hpp
        Game.hpp
        UserInterface.hpp
        Difficulty.hpp
)

set(
        assets
        ../data/data_file.txt
        ../data/empty_file.txt
        ../data/file_setsGridSizeTo_7.txt
        ../data/OpenSans.ttf
)

add_library(Code)
target_sources(Code PRIVATE ${SourceFiles} PUBLIC ${HeaderFiles})
target_link_libraries(Code PRIVATE SDL2::SDL2main SDL2::SDL2 SDL2_ttf::SDL2_ttf-static)

add_executable(MondrianBlocks main.cpp)
target_link_libraries(MondrianBlocks PRIVATE SDL2::SDL2-static SDL2::SDL2main SDL2_ttf::SDL2_ttf-static PUBLIC Code)

file(COPY ${assets} DESTINATION ${CMAKE_BINARY_DIR}/src)

if ((WIN32 OR WIN64) AND NOT MSVC)
    add_custom_command(
            TARGET MondrianBlocks POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:MondrianBlocks>"
            VERBATIM
    )
endif()