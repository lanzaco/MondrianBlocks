#pragma once
#include "Blocks.hpp"
#include <vector>

class Grid
{

public:
    Grid();
    ~Grid();
    bool checkIfPlaceable();
    void placeBlock();
    void removeBlock();
    void init();
    void setGridSize(int gridSize);

private:
    static int m_gridSize;
    std::vector<Blocks *> m_grid;
};
