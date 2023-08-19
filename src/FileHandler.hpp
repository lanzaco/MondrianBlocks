#pragma once

#include "Grid.hpp"

#include <list>
#include <string>

class FileHandler
{
public:
    FileHandler() = default;
    std::vector<Grid *> readFile(const std::string& filePath);
    void setMGrid(std::string line);
private:
    std::vector<Grid *> m_listGrid;
};
