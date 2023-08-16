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
    bool isSpotFree(const int xCoordinate, const int yCoordinate);
    void switchOrderOfNotPlacedBlocks();

    Grid* getSolverGrid();
    void setSolverGrid(Grid grid);

protected:
private:
    Grid m_grid;
};
