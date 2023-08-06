#include <SDL.h>
#include "Game.hpp"
#include "FileHandler.hpp"

int main(int argc, char *argv[])
{
    //Input is unused
    (void)argc;
    (void)argv;

    FileHandler file;
    file.readFile();

    Game game{};
    Grid grid{};
    game.run(&grid);

    return 0;
}