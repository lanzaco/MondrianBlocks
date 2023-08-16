#pragma once
#include <SDL.h>
#include <tuple>

class Blocks
{

public:
    Blocks(int x, int y, int sizeX, int sizeY, SDL_Color color, bool isRotated = false);
    Blocks() = default;
    ~Blocks() = default;
    int getX() const;
    int getY() const;
    int getSizeX() const;
    int getSizeY() const;
    bool getIsRotated() const;
    SDL_Color getColor() const;
    SDL_Rect* getRect();

    void updateRect();
    std::pair<int, int> getNewCoords();
    void setX(int x);
    void setY(int y);
    void setRotate(bool rotation);
    void rotate();

private:
    int m_x;
    int m_y;
    int m_sizeX;
    int m_sizeY;
    bool m_isRotated;
    SDL_Color m_color;
    SDL_Rect m_rect;
};
