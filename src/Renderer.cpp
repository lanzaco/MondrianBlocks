#include "Renderer.hpp"
#include "Colors.hpp"

#include <iostream>

SDL_Window *Renderer::m_window{nullptr};
SDL_Renderer *Renderer::m_renderer{nullptr};

void Renderer::init()
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::invalid_argument("Error");
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if (!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        std::cout << "SDL can not disable compositor bypass!" << std::endl;
        return 0;
    }
#endif

    m_window = SDL_CreateWindow("Grid",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                800, 800,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
    if (!m_window)
    {
        throw std::invalid_argument("SDL2 could not create the window");
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);
    if (!m_renderer)
    {
        throw std::invalid_argument("SDL2 could not create the renderer");
    }
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
