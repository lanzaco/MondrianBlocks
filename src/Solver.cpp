#include "Solver.hpp"
#include <vector>
#include <iostream>

constexpr int MAXROWS = 7;
constexpr int MAXCOLUMN = 7;

std::pair<int, int> nextCoordinates(int lastX, int lastY);
std::pair<int, int> lastCoordinates(int lastX, int lastY);

Grid Solver::solve(Grid &grid)
{
    m_grid = grid;
    int counterRuns = 0;

    while(!m_grid.checkIfWon())
    {
        if(!tryToPlaceAllBlocks())
        {
            //remove last placed block from list of blocks and add to notPlacedBlocks
            Blocks* lastPlacedBlock = m_grid.getBlocks()->back();
            int xCoordinate = lastPlacedBlock->getX();
            int yCoordinate = lastPlacedBlock->getY();

            //subtracting 1 because x-coordinate starts at 0
            std::tie(xCoordinate, yCoordinate) = nextCoordinates(xCoordinate, yCoordinate);
            lastPlacedBlock->setX(xCoordinate);
            lastPlacedBlock->setY(yCoordinate);
            //lastPlacedBlock->setRotate(false);
            m_grid.removeBlock(lastPlacedBlock);

            switchOrderOfNotPlacedBlocks();

            ++counterRuns;
            std::cout << "nein " << counterRuns << std::endl;
        }
        else
        {
            std::cout << "ja";
            break;
        }
        if(counterRuns > 1024)
        {
            m_grid.clear();
            return m_grid;
        }
    }
    return m_grid;
}

void Solver::switchOrderOfNotPlacedBlocks()
{
    //last Block of Not placed Blocks has to be first

    m_grid.getNotPlacedBlocks()->insert(m_grid.getNotPlacedBlocks()->begin(), m_grid.getNotPlacedBlocks()->back());
    m_grid.getNotPlacedBlocks()->erase(std::prev(m_grid.getNotPlacedBlocks()->end()));
}

bool Solver::tryToPlaceAllBlocks()
{
    //for(auto currentBlock : *m_grid.getNotPlacedBlocks())
    //for(int i = 0; i < m_grid.getNotPlacedBlocks()->size(); ++i)
    while(!m_grid.getNotPlacedBlocks()->empty())
    {
        Blocks* currentBlock = m_grid.getNotPlacedBlocks()->at(0);
        int notPlaceableX;
        int notPlaceableY;
        std::tie(notPlaceableX, notPlaceableY) = lastCoordinates(currentBlock->getX(), currentBlock->getY());
        bool lastRotation = currentBlock->getIsRotated();
        int xCoordinate = 0; //currentBlock->getX();
        int yCoordinate = 0; //currentBlock->getY();
        //currentBlock->setRotate(false);

        int counterRotations = 0;
        if(currentBlock->getIsRotated()) counterRotations = 1;

        while(!m_grid.checkIfPlaceable(currentBlock))
        {
            std::tie(xCoordinate, yCoordinate) = nextCoordinates(xCoordinate, yCoordinate);
            currentBlock->setX(xCoordinate);
            currentBlock->setY(yCoordinate);
            std::tie(xCoordinate, yCoordinate) = findNextFreeSpot(currentBlock);
            if(xCoordinate == notPlaceableX && yCoordinate == notPlaceableY && currentBlock->getIsRotated() == lastRotation)
            {
                //skip the last position the block was in
                std::tie(xCoordinate, yCoordinate) = nextCoordinates(xCoordinate, yCoordinate);
                currentBlock->setX(xCoordinate);
                currentBlock->setY(yCoordinate);
                std::tie(xCoordinate, yCoordinate) = findNextFreeSpot(currentBlock);
            }
            if(xCoordinate == 8 && yCoordinate == 8) // findNextFreeSpot returns (8,8) if there is no free spot remaining
            {
                //rotate
                currentBlock->setRotate(true);
                xCoordinate = 0;
                yCoordinate = 0;
                currentBlock->setX(xCoordinate);
                currentBlock->setY(yCoordinate);
                ++counterRotations;
            }
            else
            {
                currentBlock->setX(xCoordinate);
                currentBlock->setY(yCoordinate);
            }
            if(counterRotations > 1) return false;
            currentBlock->updateRect();
        }
        m_grid.placeBlock(currentBlock);
        currentBlock->updateRect();
    }
    return true;
}

std::pair<int, int> lastCoordinates(int lastX, int lastY)
{
    if(lastX == 0 && lastY == 0)
    {
        return {MAXCOLUMN, MAXROWS};
    }
    if(lastX > 0)
    {
        return {--lastX, lastY};
    }
    else
    {
        return {MAXCOLUMN, --lastY};
    }
}

std::pair<int, int> nextCoordinates(int lastX, int lastY)
{
    if(lastX == MAXCOLUMN && lastY == MAXROWS)
    {
        return {0,0};
    }
    else if(lastX == MAXCOLUMN && lastY != MAXROWS)
    {
        return {0, ++lastY};
    }
    else
    {
        return {++lastX, lastY};
    }
}

std::pair<int,int> Solver::findNextFreeSpot(const Blocks *currentBlock)
{
    int xStartCoordinate = currentBlock->getX();
    int yStartCoordinate = currentBlock->getY();
    int yMax;
    int xMax;

    if(currentBlock->getIsRotated())
    {
        xMax = Grid::getGridSize() - currentBlock->getSizeY();
        yMax = Grid::getGridSize() - currentBlock->getSizeX();
    }
    else
    {
        yMax = Grid::getGridSize() - currentBlock->getSizeY();
        xMax = Grid::getGridSize() - currentBlock->getSizeX();
    }

    while(!isSpotFree(xStartCoordinate, yStartCoordinate))
    {
        if(xStartCoordinate < xMax)
        {
            ++xStartCoordinate;
        }
        else
        {
            ++yStartCoordinate;
            xStartCoordinate = 0;
        }

        if(yStartCoordinate > yMax)
        {
            return{8, 8};
        }
    }
    return {xStartCoordinate, yStartCoordinate};
}

bool Solver::isSpotFree(const int xCoordinate, const int yCoordinate)
{
    if((m_grid.getGrid()->at(yCoordinate * Grid::getGridSize() + xCoordinate)) != nullptr)
    {
        return false;
    }
    return true;
}

Grid* Solver::getSolverGrid()
{
    return &m_grid;
}

void Solver::setSolverGrid(const Grid &grid)
{
    m_grid = grid;
}

Grid Solver::recursiveSolver(Grid grid)
{
    if (grid.getNotPlacedBlocks()->empty()) return grid;

    Blocks *currentBlock = grid.getNotPlacedBlocks()->front();
    int sizeX = currentBlock->getSizeX() - 1;
    int sizeY = currentBlock->getSizeY() - 1;

    for (int rotate = 0; (rotate < 2) && ((sizeX != sizeY) || (rotate == 0)); ++rotate) {
        if (rotate == 1) {
            currentBlock->setRotate(true);
            int tmp = sizeX;
            sizeX = sizeY;
            sizeY = tmp;
        } else {
            currentBlock->setRotate(false);
        }
        for (int yIterator = 0; yIterator < Grid::getGridSize() - sizeY; ++yIterator) {
            currentBlock->setY(yIterator);
            for (int xIterator = 0; xIterator < Grid::getGridSize() - sizeX; ++xIterator) {
                currentBlock->setX(xIterator);
                currentBlock->updateRect();
                if (grid.checkIfPlaceable(currentBlock)) {
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