#pragma once
#include <SDL.h>

class Blocks
{

public:
    Blocks(int x, int y, int sizeX, int sizeY, bool isRotated, SDL_Color color);
    ~Blocks();
    int getX() const;
    int getY() const;
    int getSizeX() const;
    int getSizeY() const;
    bool getIsRotated() const;
    SDL_Color getColor() const;
    SDL_Rect getRect() const;

private:
    int m_x;
    int m_y;
    int m_sizeX;
    int m_sizeY;
    bool m_isRotated;
    SDL_Color m_color;
    SDL_Rect m_rect;
};
