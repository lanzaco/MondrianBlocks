
#include "Game.hpp"
#include "Grid.hpp"
#include "Colors.hpp"
#include "Defines.hpp"

#include <vector>

Game::Game()
    : m_quit(false),
      m_leftMouseButtonPressed(false),
      m_mousePosition({0, 0}),
      m_clickOffset({0, 0}),
      m_selectedRect(nullptr),
      m_selectedBlock(nullptr)
{
}

void Game::moveSelectedRectWithMouse()
{
    if (m_leftMouseButtonPressed && m_selectedRect != nullptr)
    {
        m_selectedRect->x = m_mousePosition.x - m_clickOffset.x;
        m_selectedRect->y = m_mousePosition.y - m_clickOffset.y;
    }
}

void Game::handleMouseClick(Grid *grid)
{
    m_leftMouseButtonPressed = false;
    if (m_selectedBlock)
    {
        grid->moveBlock(m_selectedBlock);
    }
    m_selectedRect = nullptr;
    m_selectedBlock = nullptr;
}

void Game::selectRectWithMouse(const std::vector<SDL_Rect *> &rectangles)
{
    for (auto currentRect : rectangles)
    {
        if (SDL_PointInRect(&m_mousePosition, currentRect))
        {
            m_selectedRect = currentRect;
            m_clickOffset.x = m_mousePosition.x - currentRect->x;
            m_clickOffset.y = m_mousePosition.y - currentRect->y;
        }
    }
}

void Game::selectNotPlacedBlockWithMouse(const std::vector<Blocks *> &notPlacedBlocks)
{
    if (!notPlacedBlocks.empty())
    {
        int distance = (Grid::m_gridSize * Renderer::m_maxSizePerSquare) + 2 * GRID_MARGIN;
        Blocks *currentBlock = notPlacedBlocks.at(Grid::m_counter);
        SDL_Rect dropArea = {distance + 100 + 2 * GRID_MARGIN, GRID_MARGIN, currentBlock->getSizeX() * Renderer::m_maxSizePerSquare, currentBlock->getSizeY() * Renderer::m_maxSizePerSquare};
        if (SDL_PointInRect(&m_mousePosition, &dropArea))
        {
            m_selectedBlock = currentBlock;
            m_selectedRect = currentBlock->getRect();
        }
    }
}

void Game::handleTriangleClick()
{
    int x;
    int y;
    SDL_GetWindowSize(Renderer::m_window, &x, &y);

    int distance = (Grid::m_gridSize * Renderer::m_maxSizePerSquare) + 2 * GRID_MARGIN;
    int sizeBox = (Renderer::m_maxSizePerSquare * 5) + 2 * GRID_MARGIN;
    int width = 100;
    int height = 200;
    SDL_Rect leftTriangle{distance, y / 2 - width / 2, width, height};
    SDL_Rect rightTriangle{distance + sizeBox, y / 2 - width / 2, width, height};
    if (SDL_PointInRect(&m_mousePosition, &leftTriangle))
    {
        Grid::m_counter--;
    }

    if (SDL_PointInRect(&m_mousePosition, &rightTriangle))
    {
        Grid::m_counter++;
    }
}

Blocks *Game::findSelectedBlock(const std::vector<Blocks *> *blocks)
{
    for (auto currentBlock : *blocks)
    {
        if (m_selectedRect == currentBlock->getRect())
        {
            return currentBlock;
        }
    }
    return m_selectedBlock;
}

void Game::rotateSelectedBlock()
{
    if (m_selectedBlock != nullptr)
    {
        m_selectedBlock->rotate();
    }
}

void Game::run(Grid *grid)
{

    std::vector<SDL_Rect *> *rectangles;
    std::vector<Blocks *> *blocks;
    std::vector<Blocks *> *notPlacedBlocks;

    // Used to initialize the size of the rendered Grid
    Renderer::windowSizeChanged();

    blocks = grid->getBlocks();
    rectangles = grid->getRectangles();
    notPlacedBlocks = grid->getNotPlacedBlocks();

    while (!m_quit)
    {

        SDL_Event event;
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT)
        {
            m_quit = true;
        }

        if (event.type == SDL_MOUSEMOTION)
        {
            m_mousePosition = {event.motion.x, event.motion.y};
            moveSelectedRectWithMouse();
        }

        if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (m_leftMouseButtonPressed && event.button.button == SDL_BUTTON_LEFT)
            {
                handleMouseClick(grid);
            }
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (!m_leftMouseButtonPressed && event.button.button == SDL_BUTTON_LEFT)
            {
                m_leftMouseButtonPressed = true;

                selectRectWithMouse(*rectangles);

                selectNotPlacedBlockWithMouse(*notPlacedBlocks);

                handleTriangleClick();

                m_selectedBlock = findSelectedBlock(blocks);
            }
            if (m_leftMouseButtonPressed && event.button.button == SDL_BUTTON_RIGHT)
            {
                rotateSelectedBlock();
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

        // Draw selected Block again, so its on top of all other Rectangles
        if (m_selectedBlock)
        {
            Renderer::drawRectWithBoarder(m_selectedBlock);
        }
        if (grid->checkIfWon())
        {
            m_quit = true;
        }

        SDL_RenderPresent(Renderer::m_renderer);
    }
    Renderer::end();
}
