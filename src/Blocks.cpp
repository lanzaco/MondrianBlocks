#include "Blocks.hpp"
#include "Renderer.hpp"
#include "Defines.hpp"

#include <iostream>

Blocks::Blocks(int x, int y, int sizeX, int sizeY, SDL_Color color, bool isRotated)
    : m_x(x), m_y(y), m_sizeX(sizeX), m_sizeY(sizeY), m_isRotated(isRotated), m_color(color), m_rect()
{
    updateRect();
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

SDL_Rect* Blocks::getRect()
{
    return &m_rect;
}

void Blocks::updateRect() {
    int width = Renderer::m_maxSizePerSquare * m_sizeX - GRID_MARGIN;
    int height = Renderer::m_maxSizePerSquare * m_sizeY - GRID_MARGIN;

    int coordX = m_x * Renderer::m_maxSizePerSquare + GRID_BORDER;
    int coordY = m_y * Renderer::m_maxSizePerSquare + GRID_BORDER;
    if (m_isRotated)
    {
        int tmp = width;
        width = height;
        height = tmp;
    }
    SDL_Rect rect{coordX, coordY, width, height};
    m_rect = rect;
}

std::pair<int, int> Blocks::getNewCoords() {
    float fx = static_cast<float>(getRect()->x - GRID_BORDER) / static_cast<float>(Renderer::m_maxSizePerSquare);
    float fy = static_cast<float>(getRect()->y - GRID_BORDER) / static_cast<float>(Renderer::m_maxSizePerSquare);

    int x = static_cast<int>(round(fx));
    int y = static_cast<int>(round(fy));

    return {x,y};
}

void Blocks::setX(int x) {
    m_x = x;
}

void Blocks::setY(int y) {
    m_y = y;
}
