#include "Grid.hpp"

#include <utility>

int Grid::m_gridSize = 0;

Grid::Grid()
{
    clear();
}

Grid::Grid(std::vector<Blocks *> grid)
{
    m_grid = std::move(grid);
}

void Grid::setGridSize(int gridSize)
{
    m_gridSize = gridSize;
}

void Grid::clear()
{
    m_grid.clear();
    for (int i = 0; i < m_gridSize * m_gridSize; ++i) {
        m_grid.push_back(nullptr);
    }
}

bool Grid::checkIfPlaceable(Blocks &block)
{
    int x = block.getX();
    int sizeX = block.getSizeX();
    int y = block.getY();
    int sizeY = block.getSizeY();
    for (int i = x; i < x + sizeX; ++i) {
        for (int j = y; j < y + sizeY; ++j)
        {
            if (m_grid.at(i * m_gridSize + j) != nullptr)
            {
                if (m_grid.at(i * m_gridSize + j) != &block) return false;
            }
        }
    }
    return true;
}

void Grid::placeBlock(Blocks &block)
{
    if (checkIfPlaceable(block))
    {
        int x = block.getX();
        int sizeX = block.getSizeX();
        int y = block.getY();
        int sizeY = block.getSizeY();
        for (int i = x; i < x + sizeX; ++i)
        {
            for (int j = y; j < y + sizeY; ++j)
            {
                m_grid.at(i * m_gridSize + j) = &block;
            }
        }
    }
}

void Grid::removeBlock(Blocks &block)
{
    int x = block.getX();
    int sizeX = block.getSizeX();
    int y = block.getY();
    int sizeY = block.getSizeY();
    for (int i = x; i < x + sizeX; ++i)
    {
        for (int j = y; j < y + sizeY; ++j)
        {
            m_grid.at(i * m_gridSize + j) = nullptr;
        }
    }
}
