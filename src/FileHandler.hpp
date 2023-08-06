//
// Created by Annika Jung on 31.07.23.
//
#pragma once

#include "Grid.hpp"
#include <list>
#include <string>

class FileHandler
{
public:
    FileHandler() = default;
    std::vector<Grid *> readFile();
    void setMGrid(std::string line);

private:
    std::vector<Grid *> m_listGrid;
};
