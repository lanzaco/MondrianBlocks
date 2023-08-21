#include "Difficulty.hpp"
#include "Blocks.hpp"
#include "Grid.hpp"

#include <algorithm>
#include <vector>

int checkSurrounding(const std::vector<Blocks *> &blocks, const std::vector<Blocks *> &grid)
{
    std::vector<Blocks *> surroundingBlocks;
    for (auto currentBlock : blocks)
    {
        int x = currentBlock->getX();
        int y = currentBlock->getY();
        int sizeX = currentBlock->getSizeX();
        int sizeY = currentBlock->getSizeY();

        if (currentBlock->getIsRotated())
        {
            int tmp = sizeX;
            sizeX = sizeY;
            sizeY = tmp;
        }

        for (int yIterator = y; yIterator < y + sizeY; ++yIterator)
        {
            for (int xIterator = x; xIterator < x + sizeX; ++xIterator)
            {
                if (yIterator < Grid::m_gridSize - 2)
                {
                    Blocks *block = grid.at((yIterator + 2) * Grid::m_gridSize + (xIterator));
                    Blocks *blockInBetween = grid.at((yIterator + 1) * Grid::m_gridSize + (xIterator));
                    if (block != nullptr && block != currentBlock)
                    {

                        if (blockInBetween == nullptr)
                        {
                            surroundingBlocks.emplace_back(block);
                        }
                    }
                }

                if (yIterator > 1)
                {
                    auto block = grid.at((yIterator - 2) * Grid::m_gridSize + (xIterator));
                    auto blockInBetween = grid.at((yIterator - 1) * Grid::m_gridSize + (xIterator));
                    if (block != nullptr && block != currentBlock)
                    {
                        if (blockInBetween == nullptr)
                        {
                            surroundingBlocks.emplace_back(block);
                        }
                    }
                }

                if (xIterator < Grid::m_gridSize - 2)
                {
                    auto block = grid.at((yIterator)*Grid::m_gridSize + (xIterator + 2));
                    auto blockInBetween = grid.at((yIterator)*Grid::m_gridSize + (xIterator + 1));
                    if (block != nullptr && block != currentBlock)
                    {
                        if (blockInBetween == nullptr)
                        {
                            surroundingBlocks.emplace_back(block);
                        }
                    }
                }

                if (xIterator > 1)
                {
                    auto block = grid.at((yIterator)*Grid::m_gridSize + (xIterator - 2));
                    auto blockInBetween = grid.at((yIterator)*Grid::m_gridSize + (xIterator - 1));
                    if (block != nullptr && block != currentBlock)
                    {
                        if (blockInBetween == nullptr)
                        {
                            surroundingBlocks.emplace_back(block);
                        }
                    }
                }
            }
        }
    }

    // Erases doubled entries from vector
    for (auto currentBlock : surroundingBlocks)
    {
        auto new_end = std::remove(surroundingBlocks.begin(), surroundingBlocks.end(), currentBlock);
        surroundingBlocks.erase(new_end, surroundingBlocks.end());
        surroundingBlocks.emplace_back(currentBlock);
    }

    return static_cast<int>(surroundingBlocks.size()) / 2;
}

int checkBoarder(const std::vector<Blocks *> &blocks, const std::vector<Blocks *> &grid)
{
    int counter = 0;

    for (auto currentBlock : blocks)
    {
        int x = currentBlock->getX();
        int y = currentBlock->getY();
        int sizeX = currentBlock->getSizeX();
        int sizeY = currentBlock->getSizeY();

        if (currentBlock->getIsRotated())
        {
            int tmp = sizeX;
            sizeX = sizeY;
            sizeY = tmp;
        }

        int maxX = sizeX + x - 1;
        int maxY = sizeY + y - 1;

        if (x == 1)
        {
            bool hasBlockInBetween{false};
            for (int yIterator = y; yIterator <= maxY; ++yIterator)
            {
                if (grid.at(yIterator * Grid::m_gridSize) != nullptr)
                    hasBlockInBetween = true;
            }
            if (!hasBlockInBetween)
                ++counter;
        }

        if (y == 1)
        {
            bool hasBlockInBetween{false};
            for (int xIterator = x; xIterator <= maxX; ++xIterator)
            {
                if (grid.at(xIterator) != nullptr)
                    hasBlockInBetween = true;
            }
            if (!hasBlockInBetween)
                ++counter;
        }

        if (maxY == Grid::m_gridSize - 2)
        {
            bool hasBlockInBetween{false};
            for (int xIterator = x; xIterator <= maxX; ++xIterator)
            {
                if (grid.at(Grid::m_gridSize - 1 * Grid::m_gridSize + xIterator) != nullptr)
                    hasBlockInBetween = true;
            }
            if (!hasBlockInBetween)
                ++counter;
        }

        if (maxX == Grid::m_gridSize - 2)
        {
            bool hasBlockInBetween{false};
            for (int yIterator = y; yIterator <= maxY; ++yIterator)
            {
                if (grid.at(yIterator * Grid::m_gridSize + Grid::m_gridSize - 1) != nullptr)
                    hasBlockInBetween = true;
            }
            if (!hasBlockInBetween)
                ++counter;
        }
    }

    return counter;
}

difficulty Difficulty::getDifficulty(Grid *grid)
{
    int difficultyAsInt = 0;
    auto blocks = grid->getBlocks();
    auto playGrid = grid->getGrid();

    difficultyAsInt += checkSurrounding(*blocks, *playGrid);

    difficultyAsInt += checkBoarder(*blocks, *playGrid);

    if (difficultyAsInt == 0)
        return difficulty::hard;
    if (difficultyAsInt == 1)
        return difficulty::medium;
    if (difficultyAsInt == 2)
        return difficulty::easy;
    return difficulty::impossible;
}