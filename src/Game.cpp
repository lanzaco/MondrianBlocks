#include "Game.hpp"
#include "Grid.hpp"
#include "Colors.hpp"
#include "Defines.hpp"

#include <vector>

Game::Game()
    : m_quit(false)
    , m_leftMouseButtonPressed(false)
    , m_mousePosition({0, 0})
    , m_clickOffset({0, 0})
    , m_selectedRect(nullptr)
    , m_selectedBlock(nullptr)
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
        int x = distance + 100 + 2 * GRID_MARGIN;
        int y = GRID_MARGIN;
        int width = currentBlock->getSizeX() * Renderer::m_maxSizePerSquare;
        int height = currentBlock->getSizeY() * Renderer::m_maxSizePerSquare;
        SDL_Rect dropArea = {x, y, width, height};

        if (SDL_PointInRect(&m_mousePosition, &dropArea))
        {
            m_selectedBlock = currentBlock;
            m_selectedRect = currentBlock->getRect();
            m_selectedRect->x = dropArea.x;
            m_selectedRect->y = dropArea.y;
            m_clickOffset.x = m_mousePosition.x - currentBlock->getRect()->x;
            m_clickOffset.y = m_mousePosition.y - currentBlock->getRect()->y;
        }
    }
}

void Game::handleTriangleClick() const
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

Blocks *Game::findSelectedBlock(const std::vector<Blocks *> *blocks) const
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

bool Game::run(Grid *grid)
{
    bool playAgain{false};
    std::vector<SDL_Rect *> *rectangles;
    std::vector<Blocks *> *blocks;
    std::vector<Blocks *> *notPlacedBlocks;

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
            playAgain = false;
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

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_r && m_leftMouseButtonPressed)
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
            playAgain = UserInterface::wonGame();
        }
        SDL_RenderPresent(Renderer::m_renderer);
    }
    return playAgain;
}

Grid *Game::makeOwnGrid()
{
    Grid *grid = new Grid;
    std::vector<SDL_Rect *> *rectangles;
    std::vector<Blocks *> *blocks;
    std::vector<Blocks *> *notPlacedBlocks;
    auto *tmpNotPlacedBlocks = new std::vector<Blocks *>;
    auto *tmpBlackBlocks = new std::vector<Blocks *>;
    SDL_Rect rectFinish = Renderer::drawButton("Finish", BOTTOM_RIGHT, BLACK);

    rectangles = grid->getRectangles();
    blocks = grid->getBlocks();
    notPlacedBlocks = grid->getNotPlacedBlocks();

    for (auto currentBlock : *notPlacedBlocks)
    {
        SDL_Color color = currentBlock->getColor();
        bool isBlack = (color.r == BLACK.r) && (color.g == BLACK.g) && (color.b == BLACK.b) && (color.a == BLACK.a);
        
        if (!isBlack)
        {
            tmpNotPlacedBlocks->push_back(currentBlock);
        }
        else
        {
            tmpBlackBlocks->push_back(currentBlock);
        }
    }

    notPlacedBlocks->clear();
    *notPlacedBlocks = *tmpBlackBlocks;

    while (true)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT)
        {
            return nullptr;
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

            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (SDL_PointInRect(&m_mousePosition, &rectFinish))
                {
                    *notPlacedBlocks = *tmpNotPlacedBlocks;
                    delete tmpNotPlacedBlocks;
                    delete tmpBlackBlocks;
                    return grid;
                }
            }
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_r && m_leftMouseButtonPressed)
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

        if (notPlacedBlocks->empty())
        {
            rectFinish = Renderer::drawButton("Finish", BOTTOM_RIGHT, BLACK);
        }

        SDL_RenderPresent(Renderer::m_renderer);
    }
}
