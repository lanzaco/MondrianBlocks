#include "Blocks.hpp"

Blocks::Blocks(int x, int y, int sizeX, int sizeY, bool isRotated, SDL_Color color)
    : m_x(x)
    , m_y(y)
    , m_sizeX(sizeX)
    , m_sizeY(sizeY)
    , m_isRotated(isRotated)
    , m_color(color)
{
}

int Blocks::getX() const
{
    return m_x;
}

int Blocks::getY() const
{
    return m_y;
}

int Blocks::getSizeX() const
{
    return m_sizeX;
}

int Blocks::getSizeY() const
{
    return m_sizeY;
}

bool Blocks::getIsRotated() const
{
    return m_isRotated;
}

SDL_Color Blocks::getColor() const
{
    return m_color;
}

SDL_Rect Blocks::getRect() const
{
    return m_rect;
}