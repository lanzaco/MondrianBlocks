#include <SDL.h>
#include "Game.hpp"
#include "UserInterface.hpp"
#include "FileHandler.hpp"

int main(int argc, char *argv[])
{
    //Input is unused
    (void)argc;
    (void)argv;

    //FileHandler file;
    //file.readFile();

    UserInterface::showMenu();
    return 0;
}