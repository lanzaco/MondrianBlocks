#pragma once

#include <SDL.h>

class Renderer {
public:
    Renderer();
    static SDL_Window* m_window;
    static SDL_Renderer* m_renderer;

    void init();
};