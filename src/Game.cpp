
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
    std::vector<Blocks *>* notPlacedBlocks;

    //Used to initialize the size of the rendered Grid
    Renderer::windowSizeChanged();

    blocks = grid->getBlocks();
    rectangles = grid->getRectangles();
    notPlacedBlocks = grid->getNotPlacedBlocks();

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
                selectedRect = nullptr;
                selectedBlock = nullptr;
            }
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

                if (!notPlacedBlocks->empty())
                {
                    int distance = (Grid::m_gridSize * Renderer::m_maxSizePerSquare) + 2 * GRID_MARGIN;
                    Blocks* currentBlock = notPlacedBlocks->at(Grid::m_counter);
                    SDL_Rect dropArea = {distance + 100 + 2 * GRID_MARGIN, GRID_MARGIN, currentBlock->getSizeX()*Renderer::m_maxSizePerSquare, currentBlock->getSizeY()*Renderer::m_maxSizePerSquare};
                    if (SDL_PointInRect(&mousePosition, &dropArea))
                    {
                        selectedBlock = currentBlock;
                        selectedRect = currentBlock->getRect();
                    }
                }

                int x;
                int y;
                SDL_GetWindowSize(Renderer::m_window, &x, &y);

                int distance = (Grid::m_gridSize * Renderer::m_maxSizePerSquare) + 2 * GRID_MARGIN;
                int sizeBox = (Renderer::m_maxSizePerSquare * 5) + 2 * GRID_MARGIN;
                int width = 100;
                int height = 200;
                SDL_Rect leftTriangle{distance, y/2 - width/2, width, height};
                SDL_Rect rightTriangle{distance + sizeBox, y/2 - width/2, width, height};
                if (SDL_PointInRect(&mousePosition, &leftTriangle))
                {
                    Grid::m_counter--;
                }

                if (SDL_PointInRect(&mousePosition, &rightTriangle))
                {
                    Grid::m_counter++;
                }

                for (auto currentBlock : *blocks)
                {
                    if (selectedRect == currentBlock->getRect())
                    {
                        selectedBlock = currentBlock;
                    }
                }
            }
            if (leftMouseButtonPressed && event.button.button == SDL_BUTTON_RIGHT)
            {
                if (selectedBlock != nullptr)
                {
                    selectedBlock->rotate();
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
        grid->showMissingBlocks();

        //Draw selected Block again, so its on top of all other Rectangles
        if (selectedBlock)
        {
            Renderer::drawRectWithBoarder(selectedBlock);
        }

        SDL_RenderPresent(Renderer::m_renderer);
    }
    Renderer::end();
}
