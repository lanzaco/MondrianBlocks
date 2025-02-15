#include "UserInterface.hpp"
#include "Renderer.hpp"

#include "SDL.h"

int main(int argc, char *argv[])
{
    // Input is unused
    (void)argc;
    (void)argv;

    UserInterface::showMenu();
    Renderer::end();
    return 0;
}