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
)

add_library(Code)
target_sources(Code PRIVATE ${SourceFiles} PUBLIC ${HeaderFiles})
target_link_libraries(Code PRIVATE SDL2::SDL2main SDL2::SDL2)

add_executable(AbschlussProjekt main.cpp)
target_link_libraries(AbschlussProjekt PRIVATE SDL2::SDL2main SDL2::SDL2 PUBLIC Code)

