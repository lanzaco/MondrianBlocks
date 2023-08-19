#include "UserInterface.hpp"
#include "Renderer.hpp"
#include "Colors.hpp"
#include "Game.hpp"
#include "FileHandler.hpp"
#include "Defines.hpp"
#include "Solver.hpp"

#include <SDL.h>
#include <vector>
#include <random>

void UserInterface::showMenu()
{
    bool quit{false};
    SDL_Event event;
    SDL_Point mousePosition{0};
    Renderer::init();

    while (!quit)
    {
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            quit = true;
        }

        if (event.type == SDL_MOUSEMOTION)
        {
            mousePosition = {event.motion.x, event.motion.y};
        }

        Renderer::fillBackground(BACKGROUND_COLOR);
        Renderer::drawText("Mondrian Blocks", TOP_MIDDLE, BLACK);

        SDL_Rect rectPlay = Renderer::drawButton("PLAY", MIDDLE_MIDDLE, BLACK, 0, 100);
        SDL_Rect rectSolve = Renderer::drawButton("SOLVE", MIDDLE_MIDDLE, BLACK, 0, -100);
        SDL_Rect rectExit = Renderer::drawButton("EXIT", BOTTOM_RIGHT, RED, 50);

        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if (SDL_PointInRect(&mousePosition, &rectExit))
            {
                quit = true;
            }

            if (SDL_PointInRect(&mousePosition, &rectPlay))
            {
                Grid grid{*chooseGrid()};
                Game game;
                game.run(&grid);
                grid.deleteHeap();
                quit = true;
            }

            if (SDL_PointInRect(&mousePosition, &rectSolve))
            {
                Grid grid{*chooseGrid()};
                solverMenu(&grid);
                quit = true;
            }
        }

        SDL_RenderPresent(Renderer::m_renderer);
    }
}

Grid* UserInterface::chooseGrid()
{
    bool quit{false};
    SDL_Event event;
    SDL_Point mousePosition{0};
    Renderer::init();
    int counter{0};
    FileHandler fileHandler{};
    std::vector<Grid *> grids = fileHandler.readFile("./../../data/data_file.txt");

    if (grids.empty()) return nullptr;

    while (!quit)
    {
        Renderer::fillBackground(BACKGROUND_COLOR);

        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            quit = true;
        }

        if (event.type == SDL_MOUSEMOTION)
        {
            mousePosition = {event.motion.x, event.motion.y};
        }

        int x;
        int y;
        SDL_GetWindowSize(Renderer::m_window, &x, &y);
        auto maxSize = static_cast<float>(Renderer::m_maxSizePerSquare);
        Renderer::drawTriangle(GRID_MARGIN, static_cast<float>(y)/2, maxSize, maxSize, LEFT);
        Renderer::drawTriangle(static_cast<float>(x) - GRID_MARGIN - maxSize, static_cast<float>(y)/2, maxSize, maxSize, RIGHT);

        SDL_Rect leftTriangle{GRID_MARGIN, y/2,static_cast<int>(maxSize),static_cast<int>(maxSize)};
        SDL_Rect rightTriangle{x-GRID_MARGIN-static_cast<int>(maxSize),y/2, static_cast<int>(maxSize),static_cast<int>(maxSize)};
        SDL_Rect rectChoose = Renderer::drawButton("Choose", BOTTOM_RIGHT, BLACK, 20, 0);
        SDL_Rect rectGenerateNewGrid = Renderer::drawButton("Generate", BOTTOM_MIDDLE, BLACK);

        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if (SDL_PointInRect(&mousePosition, &leftTriangle))
            {
                --counter;
            }

            if (SDL_PointInRect(&mousePosition, &rightTriangle))
            {
                ++counter;
            }

            if (counter < 0) counter = static_cast<int>(grids.size()) - 1;

            if (counter >= static_cast<int>(grids.size())) counter = 0;

            if (SDL_PointInRect(&mousePosition, &rectChoose))
            {
                return grids.at(counter);
            }

            if (SDL_PointInRect(&mousePosition, &rectGenerateNewGrid)) {
                grids.push_back(generateGrid());
                counter = static_cast<int>(grids.size()) - 1;
            }
        }

        grids.at(counter)->drawPreview();
        SDL_RenderPresent(Renderer::m_renderer);
    }
    return nullptr;
}

void UserInterface::wonGame()
{
    bool quit{false};
    SDL_Event event;
    Renderer::init();

    while (!quit)
    {
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            quit = true;
        }

        Renderer::fillBackground(BACKGROUND_COLOR);
        Renderer::drawText("You won", TOP_MIDDLE, BLACK);
        SDL_RenderPresent(Renderer::m_renderer);
    }
}


Grid *UserInterface::generateGrid() {
    Grid *grid = new Grid;
    Solver solver;
    Grid solvedGrid;
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(0, 7);
    std::uniform_int_distribution<int> rotation(0, 1);

    do {
        Grid tmpGrid{};
        auto notPlacedBlocks = *(tmpGrid.getNotPlacedBlocks());

        for (auto currentBlock: notPlacedBlocks) {
            SDL_Color currentColor = currentBlock->getColor();
            if (currentColor.r == BLACK.r && currentColor.g == BLACK.g && currentColor.b == BLACK.b &&
                                                                          currentColor.a == BLACK.a) {
                do {
                    int xCoordinate = distribution(generator);
                    int yCoordinate = distribution(generator);
                    int rotated = rotation(generator);
                    currentBlock->setX(xCoordinate);
                    currentBlock->setY(yCoordinate);
                    currentBlock->setRotate(rotated);
                    currentBlock->updateRect();
                } while (!(tmpGrid.checkIfPlaceable(currentBlock)));
                tmpGrid.placeBlock(currentBlock);
            }
        }
        solvedGrid = solver.recursiveSolver(tmpGrid);
        *grid = tmpGrid;
    } while (!(solvedGrid.checkIfWon()));
    return grid;
}

void UserInterface::solverMenu(Grid *grid) {
    bool quit{false};
    SDL_Event event;
    Solver solver;
    Grid solvedGrid = solver.recursiveSolver(*grid);

    while (!quit) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            quit = true;
        }
        Renderer::fillBackground(GRAY);
        solvedGrid.drawPreview();
        Renderer::drawText("Finished", TOP_MIDDLE, BLACK);
        SDL_RenderPresent(Renderer::m_renderer);
    }
}