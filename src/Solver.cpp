#include "Solver.hpp"

#include <algorithm>

Grid Solver::recursiveSolver(Grid grid)
{
    if (grid.getNotPlacedBlocks()->empty()) return grid;

    Blocks *currentBlock = grid.getNotPlacedBlocks()->front();
    int sizeX = currentBlock->getSizeX() - 1;
    int sizeY = currentBlock->getSizeY() - 1;

    for (int rotate = 0; (rotate < 2) && ((sizeX != sizeY) || (rotate == 0)); ++rotate)
    {
        if (rotate == 1) {
            currentBlock->setRotate(true);
            int tmp = sizeX;
            sizeX = sizeY;
            sizeY = tmp;
        } else
        {
            currentBlock->setRotate(false);
        }
        for (int yIterator = 0; yIterator < Grid::getGridSize() - sizeY; ++yIterator)
        {
            currentBlock->setY(yIterator);
            for (int xIterator = 0; xIterator < Grid::getGridSize() - sizeX; ++xIterator)
            {
                currentBlock->setX(xIterator);
                currentBlock->updateRect();
                if (grid.checkIfPlaceable(currentBlock))
                {
                    grid.placeBlock(currentBlock);
                    if (grid.getNotPlacedBlocks()->empty()) return grid;
                    Grid newGrid = recursiveSolver(grid);
                    if (newGrid.getNotPlacedBlocks()->empty()) return newGrid;
                }
            }
        }
    }
    return grid;
}

void Solver::cleanUpGrid(Grid *grid)
{
    auto notPlacedBlocks = *grid->getNotPlacedBlocks();
    for (auto currentBlock: notPlacedBlocks)
    {
        auto new_end = std::remove(notPlacedBlocks.begin(), notPlacedBlocks.end(), currentBlock);
        notPlacedBlocks.erase(new_end, notPlacedBlocks.end());
        currentBlock->setRotate(false);
        notPlacedBlocks.emplace_back(currentBlock);
        currentBlock->updateRect();
    }

    auto placedBlocks = *grid->getBlocks();
    for (auto currentBlock: placedBlocks)
    {
        auto new_end = std::remove(placedBlocks.begin(), placedBlocks.end(), currentBlock);
        placedBlocks.erase(new_end, placedBlocks.end());
        placedBlocks.emplace_back(currentBlock);
        currentBlock->updateRect();
    }

    auto rectangles = *grid->getRectangles();
    for (auto currentReact : rectangles) {
        auto new_end = std::remove(rectangles.begin(), rectangles.end(), currentReact);
        rectangles.erase(new_end, rectangles.end());
        rectangles.emplace_back(currentReact);
    }
}
