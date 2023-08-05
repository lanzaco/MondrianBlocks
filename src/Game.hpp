#pragma once

#include "Renderer.hpp"
#include "Grid.hpp"

class Game
{
public:
    Game();
    void moveSelectedRectWithMouse();
    void handleMouseClick(Grid *grid);
    void selectRectWithMouse(const std::vector<SDL_Rect *> &rectangles);
    void selectNotPlacedBlockWithMouse(const std::vector<Blocks *> &notPlacedBlocks);
    void handleTriangleClick(SDL_Rect &leftTriangle, SDL_Rect &rightTriangle);
    Blocks *findSelectedBlock(const std::vector<Blocks *> &blocks);
    void rotateSelectedBlock();
    void run(Grid *grid);

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