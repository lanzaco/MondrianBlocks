#include "Grid.hpp"
#include "Renderer.hpp"
#include "Colors.hpp"
#include "Defines.hpp"

#include <utility>

int Grid::m_gridSize = 8;

Grid::Grid()
{
    clear();
}

Grid::Grid(std::vector<Blocks *> grid)
{
    clear();
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
        m_rects.push_back(currentBlock->getRect());
    }
    updateRectangles();
}

void Grid::setGridSize(int gridSize)
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

bool Grid::checkIfPlaceable(Blocks* block)
{
    int x;
    int y;
    std::tie(x,y) = block->getNewCoords();
    int sizeX = block->getSizeX();
    int sizeY = block->getSizeY();

    if (x < 0 || y < 0 || x + sizeX > m_gridSize || y + sizeY > m_gridSize) return false;

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

void Grid::placeBlock(Blocks* block)
{
    int x;
    int y;
    std::tie(x,y) = block->getNewCoords();
    int sizeX = block->getSizeX();
    int sizeY = block->getSizeY();
    for (auto& currentBlock : m_grid)
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

void Grid::removeBlock(Blocks &block)
{
    int x = block.getX();
    int sizeX = block.getSizeX();
    int y = block.getY();
    int sizeY = block.getSizeY();
    for (int i = y; i < y + sizeY; ++i)
    {
        for (int j = x; j < x + sizeX; ++j)
        {
            m_grid.at(i * m_gridSize + j) = nullptr;
        }
    }
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

void Grid::updateRectangles() {
    for (auto currentBlock : m_blocks)
    {
        currentBlock->updateRect();
    }
}

void Grid::draw() {
    int maxSize = Renderer::m_maxSizePerSquare;
    int border = GRID_BORDER;
    int margin = GRID_MARGIN;
    for (int i = 0; i < m_gridSize; ++i) {
        for (int j = 0; j < m_gridSize; ++j) {
            Renderer::drawRect({maxSize * j + border, maxSize * i + border,
                                maxSize - margin, maxSize - margin},WHITE);
        }
    }

    for (auto currentBlock : m_blocks) {
        Renderer::drawRectWithBoarder(currentBlock);
    }
}

void Grid::moveBlock(Blocks* block) {
    if (checkIfPlaceable(block))
    {
        placeBlock(block);
    }
    else
    {
        block->updateRect();
    }
}