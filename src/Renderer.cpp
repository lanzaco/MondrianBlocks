#include "Renderer.hpp"
#include "Colors.hpp"
#include "Defines.hpp"
#include "Grid.hpp"

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

// not zero, since the tests don't initialize the renderer
// thus breaking the program with a division by zero error
int Renderer::m_maxSizePerSquare{1};

SDL_Window* Renderer::m_window{nullptr};

SDL_Renderer* Renderer::m_renderer{nullptr};

TTF_Font* Renderer::m_font{nullptr};

void Renderer::init()
{
    //renderer already initialized
    if (m_renderer != nullptr)
    {
        return;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::invalid_argument("Cant initialize the renderer");
    }

    if (TTF_Init() != 0)
    {
        throw std::invalid_argument("Cant initialize SDL_ttf");
    }

#if _MSC_VER && !__INTEL_COMPILER
    const char filePath[] = "./../OpenSans.ttf";
#else
    const char filePath[] = "./OpenSans.ttf";
#endif

    m_font = TTF_OpenFont(filePath, 100);
    if (m_font == nullptr)
    {
        throw std::invalid_argument("Cant open the font");
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if (!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        throw std::invalid_argument("Cant bypass compositor");
    }
#endif

    m_window = SDL_CreateWindow("Grid",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                1400, 800,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
    if (!m_window)
    {
        throw std::invalid_argument("SDL2 could not create the window");
    }

    SDL_SetWindowMinimumSize(m_window, 1400, 800);

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);
    if (!m_renderer)
    {
        throw std::invalid_argument("SDL2 could not create the renderer");
    }

    //update all for logic used variables based on window size
    windowSizeChanged();
}

Renderer::Renderer()
{
    init();
}

void Renderer::drawRectWithBoarder(SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_renderer, &rect);
    SDL_SetRenderDrawColor(m_renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderDrawRect(m_renderer, &rect);
}

void Renderer::drawRect(SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_renderer, &rect);
}

void Renderer::fillBackground(SDL_Color color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_renderer);
}

void Renderer::end()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Renderer::windowSizeChanged()
{
    int gridSize{Grid::getGridSize()};
    int windowHeight;
    int windowWidth;
    SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);
    int maxSizeGrid = std::min(windowHeight, windowWidth);
    int margin = GRID_MARGIN * (gridSize - 1) + 2 * GRID_BORDER;
    int maxSizePerSquare = (maxSizeGrid - margin) / gridSize;
    m_maxSizePerSquare = maxSizePerSquare;
}

void Renderer::drawRectWithBoarder(Blocks *block)
{
    SDL_Color color = block->getColor();
    SDL_Rect* rect = block->getRect();
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_renderer, rect);
    SDL_SetRenderDrawColor(m_renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderDrawRect(m_renderer, rect);
}

void Renderer::drawTriangle(float x, float y, float width, float height,
                            orientation orientation, SDL_Color color)
{
    std::vector<SDL_Vertex> triangle;
    triangle.clear();
    switch (orientation)
    {

        case UP:
            triangle.push_back({SDL_FPoint{x + width/2, y}, color, SDL_FPoint{0}});
            triangle.push_back({SDL_FPoint{x, y + height}, color, SDL_FPoint{0}});
            triangle.push_back({SDL_FPoint{x + width, y + height}, color, SDL_FPoint{0}});
            break;
        case RIGHT:
            triangle.push_back({SDL_FPoint{x + width, y + height/2}, color, SDL_FPoint{0}});
            triangle.push_back({SDL_FPoint{x, y}, color, SDL_FPoint{0}});
            triangle.push_back({SDL_FPoint{x, y + height}, color, SDL_FPoint{0}});
            break;
        case DOWN:
            triangle.push_back({SDL_FPoint{x + width/2, y + height}, color, SDL_FPoint{0}});
            triangle.push_back({SDL_FPoint{x, y}, color, SDL_FPoint{0}});
            triangle.push_back({SDL_FPoint{x + width, y}, color, SDL_FPoint{0}});
            break;
        case LEFT:
            triangle.push_back({SDL_FPoint{x, y + height/2}, color, SDL_FPoint{0}});
            triangle.push_back({SDL_FPoint{x + width, y + height}, color, SDL_FPoint{0}});
            triangle.push_back({SDL_FPoint{x + width, y}, color, SDL_FPoint{0}});
            break;
    }
    SDL_SetRenderDrawColor(Renderer::m_renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);

    SDL_RenderGeometry(Renderer::m_renderer, nullptr, triangle.data(), static_cast<int>(triangle.size()), nullptr, 0);
}

SDL_Rect Renderer::drawButton(const std::string &text, alignment alignment, SDL_Color color, int x, int y)
{
    auto rectangle = drawText(text, alignment, color, x, y);
    SDL_SetRenderDrawColor(m_renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
    SDL_RenderFillRect(m_renderer, &rectangle);
    SDL_SetRenderDrawColor(m_renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderDrawRect(m_renderer, &rectangle);
    drawText(text, alignment, color, x, y);
    return rectangle;
}

SDL_Rect Renderer::drawText(const std::string& text, alignment alignment, SDL_Color color, int x, int y)
{
    int windowWidth;
    int windowHeight;
    SDL_Window* window = Renderer::m_window;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, text.c_str(), color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(Renderer::m_renderer, surfaceMessage);

    int textWidth = surfaceMessage->w;
    int textHeight = surfaceMessage->h;

    switch (alignment)
    {

        case TOP_LEFT:
            break;
        case TOP_MIDDLE:
            x = windowWidth/2 - textWidth/2 + x;
            break;
        case TOP_RIGHT:
            x = windowWidth - textWidth - x;
            break;
        case MIDDLE_LEFT:
            y = windowHeight/2 - textHeight/2 - y;
            break;
        case MIDDLE_MIDDLE:
            y = windowHeight/2 - textHeight/2 - y;
            x = windowWidth/2 - textWidth/2 + x;
            break;
        case MIDDLE_RIGHT:
            y = windowHeight/2 - textHeight/2 - y;
            x = windowWidth - textWidth - x;
            break;
        case BOTTOM_LEFT:
            y = windowHeight - textHeight - y;
            break;
        case BOTTOM_MIDDLE:
            y = windowHeight - textHeight - y;
            x = windowWidth/2 - textWidth/2 + x;
            break;
        case BOTTOM_RIGHT:
            y = windowHeight - textHeight - y;
            x = windowWidth - textWidth - x;
            break;
    }

    SDL_Rect MessageRect = {x, y, textWidth,textHeight};
    SDL_RenderCopy(Renderer::m_renderer, Message, nullptr, &MessageRect);
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surfaceMessage);
    return MessageRect;
}

void Renderer::drawCrown(float x, float y, float width, float height)
{
    Renderer::drawTriangle(x, y,width, height, UP, YELLOW);
    Renderer::drawTriangle(x + width / 2, y,width, height, UP, YELLOW);
    Renderer::drawTriangle(x + width, y,width, height, UP, YELLOW);

    SDL_SetRenderDrawColor(Renderer::m_renderer, RED.r, RED.g, RED.b, RED.a);
    Renderer::drawCircle(Renderer::m_renderer, static_cast<int>(x) + 70, static_cast<int>(y) + 110, 10);
    Renderer::drawCircle(Renderer::m_renderer, static_cast<int>(x) + 140, static_cast<int>(y) + 110, 10);
    SDL_SetRenderDrawColor(Renderer::m_renderer, BLUE.r, BLUE.g, BLUE.b, BLUE.a);
    Renderer::drawCircle(Renderer::m_renderer, static_cast<int>(x) + 210, static_cast<int>(y) + 110, 10);

    SDL_SetRenderDrawColor(Renderer::m_renderer, YELLOW.r, YELLOW.g, YELLOW.b, YELLOW.a);
    Renderer::drawCircle(Renderer::m_renderer, static_cast<int>(x) + 70, static_cast<int>(y) - 10, 20);
    Renderer::drawCircle(Renderer::m_renderer, static_cast<int>(x) + 140, static_cast<int>(y) - 10, 20);
    Renderer::drawCircle(Renderer::m_renderer, static_cast<int>(x) + 210, static_cast<int>(y) - 10, 20);
}

void Renderer::drawCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetX;
    int offsetY;
    int d;
    int status;

    offsetX = 0;
    offsetY = radius;
    d = radius -1;
    status = 0;

    while (offsetY >= offsetX)
    {
        //drawing lines that add up to a circle
        status += SDL_RenderDrawLine(renderer, x - offsetY, y + offsetX, x + offsetY, y + offsetX);
        status += SDL_RenderDrawLine(renderer, x - offsetX, y + offsetY, x + offsetX, y + offsetY);
        status += SDL_RenderDrawLine(renderer, x - offsetX, y - offsetY, x + offsetX, y - offsetY);
        status += SDL_RenderDrawLine(renderer, x - offsetY, y - offsetX, x + offsetY, y - offsetX);

        if (status < 0)
        {
            break;
        }

        if (d >= 2 * offsetX)
        {
            d -= 2 * offsetX + 1;
            offsetX += 1;
        }
        else if (d < 2 * (radius - offsetY))
        {
            d += 2 * offsetY - 1;
            offsetY -= 1;
        }
        else
        {
            d += 2 * (offsetY - offsetX - 1);
            offsetY -= 1;
            offsetX += 1;
        }
    }
}

