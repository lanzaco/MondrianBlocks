#pragma once

#include "Grid.hpp"
#include "Blocks.hpp"

class Solver
{
public:
    Solver() = default;
    Grid solve(Grid &grid);
    bool tryToPlaceAllBlocks();
    std::pair<int,int> findNextFreeSpot(const Blocks* currentBlock);

    bool isSpotFree(int xCoordinate, int yCoordinate);
    void switchOrderOfNotPlacedBlocks();

    Grid recursiveSolver(Grid grid);

    Grid* getSolverGrid();

    void setSolverGrid(const Grid &grid);

    void cleanUpGrid(Grid *grid);

protected:
private:
    Grid m_grid;
};
