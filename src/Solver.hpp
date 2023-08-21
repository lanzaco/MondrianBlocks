#pragma once

#include "Grid.hpp"
#include "Blocks.hpp"

class Solver
{
public:
    Solver() = default;
    Grid recursiveSolver(Grid grid);
    static void cleanUpGrid(Grid *grid);
protected:
private:
    Grid m_grid;
};
