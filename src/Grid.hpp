#pragma once
#include "Blocks.hpp"
#include <vector>

class Grid
{

public:
    Grid();
    ~Grid() = default;
    bool checkIfPlaceable();
    void placeBlock();
    void removeBlock();
    void clear();
    bool checkIfPlaceable(Blocks& block);
    void placeBlock(Blocks& block);
    void removeBlock(Blocks& block);
    void setGridSize(int gridSize);
private:
    static int m_gridSize;
    std::vector<Blocks *> m_grid;
};
