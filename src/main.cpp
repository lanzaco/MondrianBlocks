#include <SDL.h>
#include "Game.hpp"
#include "UserInterface.hpp"
#include "FileHandler.hpp"
#include "Solver.hpp"

int main(int argc, char *argv[])
{
    //Input is unused
    (void)argc;
    (void)argv;

    FileHandler file;
    Solver solver{};
    solver.solve(*file.readFile("./../../data/data_file.txt").front());

    //UserInterface::showMenu();
    return 0;
}