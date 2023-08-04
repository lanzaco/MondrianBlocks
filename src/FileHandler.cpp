//
// Created by Annika Jung on 31.07.23.
//

#include "FileHandler.hpp"
#include "Colors.hpp"
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>

Blocks *newBlock(std::vector<int> vecBlockCoordinate, int startIndex);
std::vector<int> splitStreamIntoVec(std::string line);

std::list<Grid *> FileHandler::readFile()
{
    int gridSize = 0;
    std::ifstream input_stream("/Users/annikajung/Library/Mobile Documents/com~apple~CloudDocs/Uni Stuttgart/SoSe23/C++/Abschlussprojekt/src/data_file.txt");
    // std::ifstream input_stream("../data_file.txt");
    // TODO: Relative Path

    if (!input_stream)
    {
        std::cerr << "Can't open input file!";
    }
    else
    {
        std::string line;
        while (getline(input_stream, line))
        {
            if (line.contains("Gridsize:"))
            {
                gridSize = std::stoi(line.substr(line.find("Gridsize: ") + 10, 1));
            }
            Grid::setGridSize(gridSize);
            if (line.contains("Grid:"))
            {
                setMGrid(line);
            }
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
    y = vecBlockCoordinate.at(startIndex + 1);
    sizeX = vecBlockCoordinate.at(startIndex + 2);
    sizeY = vecBlockCoordinate.at(startIndex + 3);
    auto *newBlock = new Blocks(x, y, sizeX, sizeY, BLACK);
    return newBlock;
}
