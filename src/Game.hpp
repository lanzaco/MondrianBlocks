#pragma once

#include "Renderer.hpp"
#include "Grid.hpp"

class Game
{
public:
    Game() = default;
    void run(Grid grid);

protected:
private:
    Renderer m_renderer{};
};