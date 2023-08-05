#include "Grid.hpp"
#include "Renderer.hpp"
#include "Colors.hpp"
#include "Defines.hpp"

#include <utility>
#include <tuple>
#include <vector>
#include <algorithm>

int Grid::m_gridSize = 8;

int Grid::m_counter = 0;

Grid::Grid()
{
    clear();
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 5, RED, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 4, RED, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 3, RED, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 3, 3, WHITE, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 2, WHITE, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 1, 4, BLUE, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 1, 5, BLUE, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 3, 4, YELLOW, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 1, 1, BLACK, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 1, 2, BLACK, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 1, 3, BLACK, false));
}

Grid::Grid(std::vector<Blocks *> grid)
{
    clear();
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 5, RED, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 4, RED, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 3, RED, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 3, 3, WHITE, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 2, 2, WHITE, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 1, 4, BLUE, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 1, 5, BLUE, false));
    m_notPlacedBlocks.push_back(new Blocks(0, 0, 3, 4, YELLOW, false));
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

    if (block->getIsRotated())
    {
        int tmp = sizeX;
        sizeX = sizeY;
        sizeY = tmp;
    }

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

    if (block->getIsRotated())
    {
        int tmp = sizeX;
        sizeX = sizeY;
        sizeY = tmp;
    }

    for (auto currentBlock : m_notPlacedBlocks) {
        if (currentBlock == block)
        {
            auto new_end = std::remove(m_notPlacedBlocks.begin(), m_notPlacedBlocks.end(), block);
            m_notPlacedBlocks.erase(new_end, m_notPlacedBlocks.end());

            m_rects.push_back(block->getRect());
            m_blocks.push_back(block);
        }
    }

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
}

void Grid::removeBlock(Blocks* block)
{
    int x = block->getX();
    int sizeX = block->getSizeX();
    int y = block->getY();
    int sizeY = block->getSizeY();
    for (int i = y; i < y + sizeY; ++i)
    {
        for (int j = x; j < x + sizeX; ++j)
        {
            m_grid.at(i * m_gridSize + j) = nullptr;
        }
    }

    auto new_end = std::remove(m_blocks.begin(), m_blocks.end(), block);
    m_blocks.erase(new_end, m_blocks.end());

    m_notPlacedBlocks.push_back(block);
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
        int x;
        int y;
        std::tie(x,y) = block->getNewCoords();
        int sizeX = block->getSizeX();
        int sizeY = block->getSizeY();
        bool isOutOfGrid = (x < 0) || (y < 0) || (x + sizeX >= Grid::m_gridSize) || (y + sizeY > Grid::m_gridSize);
        if (isOutOfGrid)
        {
            removeBlock(block);
        }
    }
    block->updateRect();
}

void Grid::showMissingBlocks() {
    int width = 100;
    int height = 100;
    int x;
    int y;
    SDL_GetWindowSize(Renderer::m_window, &x, &y);

    int distance = (Grid::m_gridSize * Renderer::m_maxSizePerSquare) + 2 * GRID_MARGIN;
    int sizeBox = (Renderer::m_maxSizePerSquare * 5) + 2 * GRID_MARGIN;

    Renderer::drawRectangle(static_cast<float>(distance), static_cast<float>(y)/2, static_cast<float>(width), static_cast<float>(height), LEFT);
    Renderer::drawRectangle(static_cast<float>(distance + sizeBox), static_cast<float>(y)/2, static_cast<float>(width), static_cast<float>(height), RIGHT);

    if (m_counter < 0) m_counter = static_cast<int>(m_notPlacedBlocks.size()) - 1;
    if (m_counter >= m_notPlacedBlocks.size()) m_counter = 0;

    if (!m_notPlacedBlocks.empty())
    {
        Blocks* currentBlock = m_notPlacedBlocks.at(m_counter);
        SDL_Rect blockRect {distance + width + 2 * GRID_MARGIN, GRID_MARGIN, currentBlock->getSizeX()*Renderer::m_maxSizePerSquare, currentBlock->getSizeY()*Renderer::m_maxSizePerSquare};
        Renderer::drawRectWithBoarder(blockRect, currentBlock->getColor());
    }
}

std::vector<Blocks *> *Grid::getNotPlacedBlocks() {
    return &m_notPlacedBlocks;
}

bool Grid::checkIfWon()
{
    
    if (!m_notPlacedBlocks.empty())
    {
        return false;
    }

 
    for (int i = 0; i < m_gridSize * m_gridSize; ++i)
    {
        if (m_grid.at(i) == nullptr)
        {
            return false;
        }
    }

   
    return true;
}
