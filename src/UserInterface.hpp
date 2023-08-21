#pragma once

#include "Grid.hpp"

class UserInterface
{
public:
    static void showMenu();
    static Grid *chooseGrid();
    static bool wonGame();
    static bool solverMenu(Grid *grid);

private:
    static bool m_quit;
};