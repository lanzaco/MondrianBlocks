#pragma once
#include "Blocks.hpp"
#include <vector>

class Grid
{

public:
    Grid();
    explicit Grid(std::vector<Blocks *> grid);
    ~Grid() = default;
    void clear();
    bool checkIfPlaceable(Blocks* block);
    void placeBlock(Blocks* block);
    void removeBlock(Blocks& block);
    static void setGridSize(int gridSize);
    static int getGridSize();
    std::vector<Blocks*>* getBlocks();
    std::vector<SDL_Rect*>* getRectangles();
    void updateRectangles();
    void draw();
    void moveBlock(Blocks* block);
private:
    static int m_gridSize;
    std::vector<Blocks *> m_grid;
    std::vector<Blocks *> m_blocks;
    std::vector<SDL_Rect *> m_rects;
};
