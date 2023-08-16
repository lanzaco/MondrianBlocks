#pragma once

#include "Grid.hpp"

class UserInterface {
public:
    static void showMenu();
    static Grid* chooseGrid();
    static void wonGame();
};
