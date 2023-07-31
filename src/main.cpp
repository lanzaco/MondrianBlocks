#include <SDL.h>

#include "Renderer.hpp"
#include "FileHandler.hpp"

int main(int argc, char *argv[])
{
    //Input is unused
    (void)argc;
    (void)argv;
    Renderer renderer{};

    FileHandler file;
    file.readFile();

    return 0;
}