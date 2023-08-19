#include "FileHandler.hpp"
#include "Colors.hpp"

#include <utility>
#include <vector>
#include <fstream>
#include <regex>
#include <string>
#include <iostream>

Blocks *newBlock(std::vector<int> vecBlockCoordinate, int startIndex);
std::vector<int> splitStreamIntoVec(std::string line);

std::vector<Grid *> FileHandler::readFile(const std::string& filePath)
{
    int gridSize;
    std::ifstream input_stream(filePath);

    if (!input_stream)
    {
        std::cerr << "Can't open input file!" << std::endl;
        return m_listGrid;
    }

    std::string line;
    while (getline(input_stream, line))
    {
        if (line.contains("Gridsize:"))
        {
            gridSize = std::stoi(line.substr(line.find("Gridsize: ") + 10, 1));
            Grid::setGridSize(gridSize);
        }
        if (line.contains("Grid:"))
        {
            setMGrid(line);
        }
    }
    return m_listGrid;
}

void FileHandler::setMGrid(std::string line)
{
    std::vector<Blocks *> vecBlocks;
    std::vector<int> vecBlockCoordinate = splitStreamIntoVec(std::move(line));

    for (int startIndex = 0; startIndex < vecBlockCoordinate.size(); startIndex += 4)
    {
        vecBlocks.push_back(newBlock(vecBlockCoordinate, startIndex));
    }

    m_listGrid.push_back(new Grid(vecBlocks));
    vecBlockCoordinate.clear();
    vecBlocks.clear();
}

std::vector<int> splitStreamIntoVec(std::string line)
{
    std::vector<int> vecBlockCoordinate;
    std::regex regex(R"(\d+)"); // matches a sequence of digits
    std::smatch match;

    while (std::regex_search(line, match, regex))
    {
        vecBlockCoordinate.push_back(std::stoi(match.str()));
        line = match.suffix();
    }
    return vecBlockCoordinate;
}

Blocks *newBlock(std::vector<int> vecBlockCoordinate, int startIndex)
{
    int x;
    int y;
    int sizeX;
    int sizeY;
    x = vecBlockCoordinate.at(startIndex);
    y = vecBlockCoordinate.at(++startIndex);
    sizeX = vecBlockCoordinate.at(++startIndex);
    sizeY = vecBlockCoordinate.at(++startIndex);
    auto *newBlock = new Blocks(x, y, sizeX, sizeY, BLACK);
    return newBlock;
}
