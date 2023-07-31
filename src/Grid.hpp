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
    static void setGridSize(int gridSize);

    bool checkIfPlaceable(Blocks& block);
    void placeBlock(Blocks& block);
    void removeBlock(Blocks& block);
    void init();
    void setGridSize(int gridSize);
    std::vector<Blocks*> getGrid();

private:
    static int m_gridSize;
    std::vector<Blocks *> m_grid;
};
