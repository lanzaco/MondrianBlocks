#pragma once

#include <SDL.h>
#include "Blocks.hpp"

class Renderer
{
public:
    Renderer();
    static void init();
    static void end();
    static void drawRectWithBoarder(SDL_Rect rect, SDL_Color color);
    static void drawRectWithBoarder(Blocks* block);
    static void drawRect(SDL_Rect rect, SDL_Color color);
    static void fillBackground(SDL_Color color);
    static void windowSizeChanged();

    static SDL_Window* m_window;
    static SDL_Renderer* m_renderer;
    static int m_maxSizePerSquare;
};