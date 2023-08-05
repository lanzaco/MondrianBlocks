#include "UserInterface.hpp"
#include "Renderer.hpp"
#include "Colors.hpp"

#include <SDL.h>

void UserInterface::showMenue()
{
    SDL_Renderer* renderer = Renderer::m_renderer;
    Renderer::fillBackground(WHITE);
    int x;
    int y;
    SDL_Window* window = Renderer::m_window;
    SDL_GetWindowSize(window, &x, &y);
}
