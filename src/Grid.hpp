#pragma once
#include "Blocks.hpp"
#include <vector>

enum class difficulty {
    easy,
    medium,
    hard,
    impossible,
};

class Grid
{

public:
    Grid();
    explicit Grid(std::vector<Blocks *> grid);
    ~Grid() = default;

    void clear();
    bool checkIfPlaceable(Blocks* block) const;
    void placeBlock(Blocks* block);
    void removeBlock(Blocks* block);
    void updateRectangles();
    void draw() const;
    void drawPreview();
    void moveBlock(Blocks* block);
    void showMissingBlocks() const;
    bool checkIfWon() const;
    difficulty getDifficulty();
    bool gridContainsBlock(const Blocks *block) const;

    static void setGridSize(const int gridSize);

    static int getGridSize();
    std::vector<Blocks*>* getBlocks();
    std::vector<SDL_Rect*>* getRectangles();
    std::vector<Blocks*>* getNotPlacedBlocks();
    std::vector<Blocks*>* getGrid();

    static int m_counter;
    static int m_gridSize;
private:
    std::vector<Blocks *> m_grid;
    std::vector<Blocks *> m_blocks;
    std::vector<SDL_Rect *> m_rects;
    std::vector<Blocks *> m_notPlacedBlocks;
};
