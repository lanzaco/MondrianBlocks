#include <SDL.h>

#include "UserInterface.hpp"

int main(int argc, char *argv[])
{
    //Input is unused
    (void)argc;
    (void)argv;

    UserInterface::showMenu();
    return 0;
}