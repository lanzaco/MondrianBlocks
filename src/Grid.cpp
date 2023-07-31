#include "Grid.hpp"

int Grid::m_gridSize = 0;

Grid::Grid()
{
}
Grid::~Grid()
{
}
void Grid::setGridSize(int gridSize)
{
    m_gridSize = gridSize;
}
bool Grid::checkIfPlaceable()
{
}
void Grid::placeBlock()
{
}
void Grid::removeBlock()
{
}
void Grid::init()
{
}

std::vector<Blocks *> Grid::getGrid() {
    return m_grid;
}
