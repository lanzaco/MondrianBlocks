
#include "Game.hpp"
#include "Grid.hpp"
#include "Colors.hpp"
#include "Defines.hpp"

#include <vector>

void Game::run(Grid* grid)
{
    bool quit{false};
    bool leftMouseButtonPressed{false};
    SDL_Point mousePosition{0,0};
    SDL_Point clickOffset{0,0};
    SDL_Rect *selectedRect{nullptr};
    Blocks *selectedBlock{nullptr};
    std::vector<SDL_Rect *>* rectangles;
    std::vector<Blocks *>* blocks;
    Renderer::windowSizeChanged();

    blocks = grid->getBlocks();
    rectangles = grid->getRectangles();

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
                if (selectedBlock)
                {
                    grid->moveBlock(selectedBlock);
                }
            }
            selectedRect = nullptr;
            selectedBlock = nullptr;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (!leftMouseButtonPressed && event.button.button == SDL_BUTTON_LEFT)
            {
                leftMouseButtonPressed = true;

                for (auto currentRect : *rectangles)
                {
                    if (SDL_PointInRect(&mousePosition, currentRect))
                    {
                        selectedRect = currentRect;
                        clickOffset.x = mousePosition.x - currentRect->x;
                        clickOffset.y = mousePosition.y - currentRect->y;
                    }
                }

                for (auto currentBlock : *blocks)
                {
                    if (selectedRect == currentBlock->getRect())
                    {
                        selectedBlock = currentBlock;
                    }
                }
            }
        }

        if (event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            Renderer::windowSizeChanged();
            grid->updateRectangles();
        }

        Renderer::fillBackground(BACKGROUND_COLOR);

        grid->draw();

        //Draw selected Block again, so its on top of all other Rectangles
        if (selectedBlock)
        {
            Renderer::drawRectWithBoarder(selectedBlock);
        }

        SDL_RenderPresent(Renderer::m_renderer);
    }
    Renderer::end();
}
