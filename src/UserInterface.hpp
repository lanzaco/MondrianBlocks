#pragma once

#include "Grid.hpp"

class UserInterface {
public:
    static void showMenu();
    static Grid* chooseGrid();

    static Grid *generateGrid();
    static void wonGame();

    static void solverMenu(Grid *grid);
};
