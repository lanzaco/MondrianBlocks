cmake_minimum_required(VERSION 3.23)

set(
        SourceFiles
        Grid.cpp
        Blocks.cpp
)

set(
        HeaderFiles
        Grid.hpp
        Blocks.hpp
        Solver.cpp
        Solver.hpp
)

add_library(Code)
target_sources(Code PRIVATE ${SourceFiles} PUBLIC ${HeaderFiles})
target_link_libraries(Code PRIVATE SDL2::SDL2main SDL2::SDL2)

add_executable(AbschlussProjekt main.cpp)
target_link_libraries(AbschlussProjekt PRIVATE SDL2::SDL2main SDL2::SDL2 PUBLIC Code)

if (WIN32 OR WIN64)
    add_custom_command(
            TARGET AbschlussProjekt POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            VERBATIM
    )
endif()