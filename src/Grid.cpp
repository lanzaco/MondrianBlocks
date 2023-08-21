#include "Grid.hpp"
#include "Renderer.hpp"
#include "Colors.hpp"
#include "Defines.hpp"
#include "Solver.hpp"

#include <utility>
#include <tuple>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <random>

int Grid::m_gridSize = 8;

int Grid::m_counter = 0;

Grid::Grid()
{
    clear();

    // This order speeds up the recursive solver
    // by first placing the 1x blocks, then the bigger
    // ones

    m_notPlacedBlocks.push_back(new Blocks(0, 0, 1, 1, BLACK, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 1, 2, BLACK, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 1, 3, BLACK, false));

    m_notPlacedBlocks.push_back(new Blocks(0, 0, 1, 4, BLUE, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 1, 5, BLUE, false));

    m_notPlacedBlocks.push_back(new Blocks(0, 0, 3, 4, YELLOW, false));

    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 5, RED, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 4, RED, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 3, RED, false));

    m_notPlacedBlocks.push_back(new Blocks(0, 0, 3, 3, WHITE, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 2, WHITE, false));
}

Grid::Grid(std::vector<Blocks *> grid)
{
    clear();

    // This order speeds up the recursive solver
    // by first placing the 1x blocks, then the bigger
    // ones
    //
    // The black blocks have to be in the vector, so they are already placed
    // Thus the size of the vector has to be the three black blocks

    if (grid.size() != BLACK_BLOCK_COUNT)
    {
        throw std::invalid_argument("The grid your trying to use is wrong");
    }

    m_notPlacedBlocks.push_back(new Blocks(0, 0, 1, 4, BLUE, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 1, 5, BLUE, false));

    m_notPlacedBlocks.push_back(new Blocks(0, 0, 3, 4, YELLOW, false));

    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 5, RED, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 4, RED, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 3, RED, false));

    m_notPlacedBlocks.push_back(new Blocks(0, 0, 3, 3, WHITE, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 2, WHITE, false));

    m_blocks = std::move(grid);

    for (auto currentBlock : m_blocks)
    {
        int x = currentBlock->getX();
        int y = currentBlock->getY();
        int sizeX = currentBlock->getSizeX();
        int sizeY = currentBlock->getSizeY();

        for (int i = y; i < y + sizeY; ++i)
        {
            for (int j = x; j < x + sizeX; ++j)
            {
                m_grid.at(i * Grid::m_gridSize + j) = currentBlock;
            }
        }
        SDL_Color color = currentBlock->getColor();
        bool isBlack = (color.r == BLACK.r) && (color.g == BLACK.g) && (color.b == BLACK.b) && (color.a == BLACK.a);

        if (!isBlack)
        {
            m_rects.push_back(currentBlock->getRect());
        }
    }
    updateRectangles();
}

void Grid::setGridSize(const int gridSize)
{
    m_gridSize = gridSize;
}

void Grid::clear()
{
    m_grid.clear();

    for (int i = 0; i < m_gridSize * m_gridSize; ++i)
    {
        m_grid.push_back(nullptr);
    }
}

bool Grid::checkIfPlaceable(Blocks *block) const
{
    int x;
    int y;
    std::tie(x, y) = block->getNewCoords();
    int sizeX = block->getSizeX();
    int sizeY = block->getSizeY();

    if (block->getIsRotated())
    {
        int tmp = sizeX;
        sizeX = sizeY;
        sizeY = tmp;
    }

    if (x < 0 || y < 0 || x + sizeX > m_gridSize || y + sizeY > m_gridSize)
        return false;

    for (int i = y; i < y + sizeY; ++i)
    {
        for (int j = x; j < x + sizeX; ++j)
        {
            if (m_grid.at(i * m_gridSize + j) != nullptr)
            {
                if (m_grid.at(i * m_gridSize + j) != block)
                    return false;
            }
        }
    }
    return true;
}

void Grid::placeBlock(Blocks *block)
{
    int x;
    int y;
    std::tie(x, y) = block->getNewCoords();
    int sizeX = block->getSizeX();
    int sizeY = block->getSizeY();

    if (block->getIsRotated())
    {
        int tmp = sizeX;
        sizeX = sizeY;
        sizeY = tmp;
    }

    auto new_end = std::remove(m_notPlacedBlocks.begin(), m_notPlacedBlocks.end(), block);
    m_notPlacedBlocks.erase(new_end, m_notPlacedBlocks.end());

    if (!gridContainsBlock(block))
    {
        m_rects.push_back(block->getRect());
        m_blocks.push_back(block);
    }

    for (auto &currentBlock : m_grid)
    {
        if (currentBlock == block)
        {
            currentBlock = nullptr;
        }
    }

    for (int i = y; i < y + sizeY; ++i)
    {
        for (int j = x; j < x + sizeX; ++j)
        {
            m_grid.at(i * m_gridSize + j) = block;
        }
    }

    block->setX(x);
    block->setY(y);
    block->updateRect();
}

void Grid::removeBlock(Blocks *block)
{
    for (auto &currentBlock : m_grid)
    {
        if (currentBlock == block)
        {
            currentBlock = nullptr;
        }
    }

    auto new_end = std::remove(m_blocks.begin(), m_blocks.end(), block);
    m_blocks.erase(new_end, m_blocks.end());

    m_notPlacedBlocks.push_back(block);
    block->updateRect();
}

int Grid::getGridSize()
{
    return m_gridSize;
}

std::vector<Blocks *> *Grid::getBlocks()
{
    return &m_blocks;
}

std::vector<SDL_Rect *> *Grid::getRectangles()
{
    return &m_rects;
}

std::vector<Blocks *> *Grid::getGrid()
{
    return &m_grid;
}

void Grid::updateRectangles()
{
    for (auto currentBlock : m_blocks)
    {
        currentBlock->updateRect();
    }
}

void Grid::draw() const
{
    int maxSize = Renderer::m_maxSizePerSquare;
    int border = GRID_BORDER;
    int margin = GRID_MARGIN;

    for (int i = 0; i < m_gridSize; ++i)
    {
        for (int j = 0; j < m_gridSize; ++j)
        {
            Renderer::drawRect({maxSize * j + border, maxSize * i + border,
                                maxSize - margin, maxSize - margin},
                               WHITE);
        }
    }

    for (auto currentBlock : m_blocks)
    {
        Renderer::drawRectWithBoarder(currentBlock);
    }
}

void Grid::drawPreview()
{
    int x;
    int y;
    SDL_GetWindowSize(Renderer::m_window, &x, &y);

    int maxSize = std::min(x, y) / (2 * m_gridSize);
    int margin = GRID_MARGIN;
    int xOffset = (x / 2 - (maxSize * m_gridSize) / 2);
    int yOffset = (y / 2 - (maxSize * m_gridSize) / 2);

    for (int yIterator = 0; yIterator < m_gridSize; ++yIterator)
    {
        for (int xIterator = 0; xIterator < m_gridSize; ++xIterator)
        {
            Renderer::drawRect({maxSize * xIterator + xOffset, maxSize * yIterator + yOffset,
                                maxSize - margin, maxSize - margin},
                               WHITE);
        }
    }

    for (auto currentBlock : m_blocks)
    {
        int xPosition = currentBlock->getX() * maxSize + xOffset;
        int yPosition = currentBlock->getY() * maxSize + yOffset;
        int width = currentBlock->getSizeX() * maxSize - margin;
        int height = currentBlock->getSizeY() * maxSize - margin;
        if (currentBlock->getIsRotated())
        {
            int tmp = width;
            width = height;
            height = tmp;
        }
        SDL_Rect previewRect = {xPosition, yPosition, width, height};
        Renderer::drawRectWithBoarder(previewRect, currentBlock->getColor());
    }
}

void Grid::moveBlock(Blocks *block)
{
    if (checkIfPlaceable(block))
    {
        placeBlock(block);
    }
    else
    {
        int x;
        int y;
        std::tie(x, y) = block->getNewCoords();
        int sizeX = block->getSizeX();
        int sizeY = block->getSizeY();
        bool isOutOfGrid = (x < 0) || (y < 0) || (x + sizeX >= Grid::m_gridSize) || (y + sizeY > Grid::m_gridSize);
        if (isOutOfGrid)
        {
            removeBlock(block);
            block->setRotate(false);
        }
    }
    block->updateRect();
}

void Grid::showMissingBlocks() const
{
    int width = 100;
    int height = 100;
    int x;
    int y;
    SDL_GetWindowSize(Renderer::m_window, &x, &y);

    int distance = (Grid::m_gridSize * Renderer::m_maxSizePerSquare) + 2 * GRID_MARGIN;
    int sizeBox = (Renderer::m_maxSizePerSquare * 5) + 2 * GRID_MARGIN;

    Renderer::drawTriangle(static_cast<float>(distance), static_cast<float>(y) / 2,
                           static_cast<float>(width),
                           static_cast<float>(height), LEFT);
    Renderer::drawTriangle(static_cast<float>(distance + sizeBox), static_cast<float>(y) / 2,
                           static_cast<float>(width),
                           static_cast<float>(height), RIGHT);

    if (m_counter < 0)
        m_counter = static_cast<int>(m_notPlacedBlocks.size()) - 1;

    if (m_counter >= m_notPlacedBlocks.size())
        m_counter = 0;

    if (!m_notPlacedBlocks.empty())
    {
        Blocks *currentBlock = m_notPlacedBlocks.at(m_counter);
        SDL_Rect blockRect{distance + width + 2 * GRID_MARGIN, GRID_MARGIN, currentBlock->getSizeX() * Renderer::m_maxSizePerSquare, currentBlock->getSizeY() * Renderer::m_maxSizePerSquare};
        Renderer::drawRectWithBoarder(blockRect, currentBlock->getColor());
    }
}

std::vector<Blocks *> *Grid::getNotPlacedBlocks()
{
    return &m_notPlacedBlocks;
}

bool Grid::checkIfWon() const
{
    return std::ranges::none_of(m_grid.cbegin(), m_grid.cend(),
                                [](Blocks *block)
                                { return block == nullptr; });
}

bool Grid::gridContainsBlock(const Blocks *block) const
{
    return std::ranges::any_of(m_grid.cbegin(), m_grid.cend(),
                               [block](Blocks *currentBlock)
                               { return currentBlock == block; });
}

// All Grids use the same Blocks in heap, so the destructor cant delete them
void Grid::deleteHeap()
{
    if (m_blocks.empty())
        return;

    if (m_notPlacedBlocks.empty())
        return;

    for (auto currentBlock : m_blocks)
    {
        delete currentBlock;
    }
    m_blocks.clear();

    for (auto currentBlock : m_notPlacedBlocks)
    {
        delete currentBlock;
    }
    m_notPlacedBlocks.clear();
}

Grid *Grid::generateGrid()
{
    auto grid = new Grid;
    Solver solver;
    Grid solvedGrid;
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(0, 7);
    std::uniform_int_distribution<int> rotation(0, 1);

    do
    {
        Grid tmpGrid{};
        auto notPlacedBlocks = *(tmpGrid.getNotPlacedBlocks());

        for (auto currentBlock : notPlacedBlocks)
        {
            SDL_Color currentColor = currentBlock->getColor();

            if (currentColor.r == BLACK.r && currentColor.g == BLACK.g && currentColor.b == BLACK.b &&
                currentColor.a == BLACK.a)
            {
                do
                {
                    int xCoordinate = distribution(generator);
                    int yCoordinate = distribution(generator);
                    int rotated = rotation(generator);
                    currentBlock->setX(xCoordinate);
                    currentBlock->setY(yCoordinate);
                    currentBlock->setRotate(rotated);
                    currentBlock->updateRect();
                } while (!(tmpGrid.checkIfPlaceable(currentBlock)));
                tmpGrid.placeBlock(currentBlock);
            }
        }
        solvedGrid = solver.recursiveSolver(tmpGrid);
        *grid = tmpGrid;
    } while (!(solvedGrid.checkIfWon()));
    Solver::cleanUpGrid(grid);
    return grid;
}