#pragma once

#include "Grid.hpp"

enum class difficulty
{
    easy,
    medium,
    hard,
    impossible,
};

class Difficulty
{
public:
    static difficulty getDifficulty(Grid *grid);
};