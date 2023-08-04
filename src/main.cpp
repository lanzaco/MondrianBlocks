#include <SDL.h>
#include "Game.hpp"
#include "Colors.hpp"
#include "Blocks.hpp"

int main(int argc, char *argv[])
{
    //Input is unused
    (void)argc;
    (void)argv;

    //FileHandler file;
    //file.readFile();

    std::vector<Blocks*> blocks;

    //m_blocks.push_back(new Blocks(0, 3, 2, 5, RED, false));
    //m_blocks.push_back(new Blocks(2, 4, 2, 4, RED, false));
    blocks.push_back(new Blocks(3, 1, 2, 3, RED, false));
    blocks.push_back(new Blocks(4, 4, 3, 3, WHITE, false));
    //m_blocks.push_back(new Blocks(1, 1, 2, 2, WHITE, false));
    //m_blocks.push_back(new Blocks(7, 4, 1, 4, BLUE, false));
    //m_blocks.push_back(new Blocks(0, 0, 1, 5, BLUE, true));
    //m_blocks.push_back(new Blocks(5, 0, 3, 4, YELLOW, false));
    //m_blocks.push_back(new Blocks(2, 3, 1, 1, BLACK, false));
    //m_blocks.push_back(new Blocks(0, 1, 1, 2, BLACK, false));
    //m_blocks.push_back(new Blocks(4, 7, 1, 3, BLACK, true));

    Game game{};
    Grid grid{blocks};
    Game::run(&grid);

    return 0;
}