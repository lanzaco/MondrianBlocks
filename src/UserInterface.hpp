#pragma once

#include "Grid.hpp"

class UserInterface {
public:
    static void showMenu();
    static Grid* chooseGrid();
    static Grid *generateGrid();

    static bool wonGame();

    static bool solverMenu(Grid *grid);
};
