#include <SDL.h>
#include "Game.hpp"

int main(int argc, char *argv[])
{
    //Input is unused
    (void)argc;
    (void)argv;

    //FileHandler file;
    //file.readFile();

    Game game{};
    game.run(Grid());

    return 0;
}