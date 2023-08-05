#pragma once

#include "Renderer.hpp"
#include "Grid.hpp"

class Game
{
public:
    Game();
    void run(Grid* grid);

protected:
private:
    bool m_quit;
    bool m_leftMouseButtonPressed;
    SDL_Point m_mousePosition;
    SDL_Point m_clickOffset;
    SDL_Rect *m_selectedRect;
    Blocks *m_selectedBlock;
    Renderer m_renderer{};
};