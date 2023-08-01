#pragma once
#include "Blocks.hpp"
#include <vector>

class Grid
{

public:
    Grid();
    Grid(std::vector<Blocks *> grid);
    ~Grid() = default;
    bool checkIfPlaceable();
    void placeBlock();
    void removeBlock();
    void clear();
    bool checkIfPlaceable(Blocks& block);
    void placeBlock(Blocks& block);
    void removeBlock(Blocks& block);
    static void setGridSize(int gridSize);
private:
    static int m_gridSize;
    std::vector<Blocks *> m_grid;
};
