#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Blocks.hpp"
#include "Colors.hpp"

enum orientation
{
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

enum alignment
{
    TOP_LEFT,
    TOP_MIDDLE,
    TOP_RIGHT,
    MIDDLE_LEFT,
    MIDDLE_MIDDLE,
    MIDDLE_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_MIDDLE,
    BOTTOM_RIGHT,
};

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
    static void drawTriangle(float x, float y, float width, float height, orientation orientation, SDL_Color color = BLACK);
    static SDL_Rect drawText(const std::string& text, alignment alignment, SDL_Color color, int x = 0, int y = 0);
    static void drawCrown(float x, float y, float width, float height);
    static void drawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);

    static SDL_Window* m_window;
    static SDL_Renderer* m_renderer;
    static int m_maxSizePerSquare;
    static TTF_Font* m_font;
};