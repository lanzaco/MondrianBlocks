
#include "Game.hpp"
#include "Renderer.hpp"
#include "Grid.hpp"
#include "Colors.hpp"

#include <list>

void Game::run(Grid grid)
{
    bool quit{false};
    bool leftMouseButtonPressed{false};
    SDL_Point mousePosition{};
    SDL_Point clickOffset{};
    SDL_Rect *selectedRect{nullptr};
    Blocks *selectedBlock{nullptr};
    std::list<SDL_Rect *> rectangles; // TODO: get all rectangles
    std::list<Blocks *> blocks;       // TODO: get all blocks

    while (!quit)
    {

        SDL_Event event;
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT)
        {
            quit = true;
        }

        if (event.type == SDL_MOUSEMOTION)
        {
            mousePosition = {event.motion.x, event.motion.y};
            if (leftMouseButtonPressed && selectedRect != nullptr)
            {
                selectedRect->x = mousePosition.x - clickOffset.x;
                selectedRect->y = mousePosition.y - clickOffset.y;
            }
        }

        if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (leftMouseButtonPressed && event.button.button == SDL_BUTTON_LEFT)
            {
                leftMouseButtonPressed = false;
                for (auto currentBlock : blocks)
                {
                    // TODO: move Block
                }
            }
            selectedRect = nullptr;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (!leftMouseButtonPressed && event.button.button == SDL_BUTTON_LEFT)
            {
                leftMouseButtonPressed = true;

                for (auto currentRect : rectangles)
                {
                    if (SDL_PointInRect(&mousePosition, currentRect))
                    {
                        selectedRect = currentRect;
                        clickOffset.x = mousePosition.x - currentRect->x;
                        clickOffset.y = mousePosition.y - currentRect->y;
                    }
                }
            }
        }

        if (event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            for (auto currentBlock : blocks)
            {
                // TODO: update Rectangle
                currentBlock;
            }
        }

        Renderer::fillBackground(GRAY);

        // TODO: draw Grid

        SDL_RenderPresent(Renderer::m_renderer);
    }
    Renderer::end();
}
