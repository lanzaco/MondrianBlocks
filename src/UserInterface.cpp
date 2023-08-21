#include "UserInterface.hpp"
#include "Renderer.hpp"
#include "Colors.hpp"
#include "Game.hpp"
#include "FileHandler.hpp"
#include "Defines.hpp"
#include "Solver.hpp"
#include "Difficulty.hpp"

#include <SDL.h>
#include <vector>

bool UserInterface::m_quit = false;

void UserInterface::showMenu()
{
    bool quit{false};
    SDL_Event event;
    SDL_Point mousePosition{0};
    Renderer::init();
    Grid *grid{nullptr};

    while (!quit && !m_quit)
    {
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            quit = true;
            m_quit = true;
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
                delete grid;
                grid = chooseGrid();
                if (grid != nullptr)
                {
                    Game game;
                    quit = !game.run(grid);
                }
            }

            if (SDL_PointInRect(&mousePosition, &rectSolve))
            {
                delete grid;
                grid = chooseGrid();
                if (grid != nullptr)
                {
                    quit = !solverMenu(grid);
                }
            }
        }

        SDL_RenderPresent(Renderer::m_renderer);
    }
    if (grid != nullptr)
    {
        grid->deleteHeap();
        delete grid;
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
    std::vector<Grid *> grids = fileHandler.readFile("./data_file.txt");

    if (grids.empty()) return nullptr;

    while (!quit && !m_quit) {
        Renderer::fillBackground(BACKGROUND_COLOR);

        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT) {
            quit = true;
            m_quit = true;
        }

        if (event.type == SDL_MOUSEMOTION) {
            mousePosition = {event.motion.x, event.motion.y};
        }

        int x;
        int y;
        SDL_GetWindowSize(Renderer::m_window, &x, &y);
        auto maxSize = static_cast<float>(Renderer::m_maxSizePerSquare);
        Renderer::drawTriangle(GRID_MARGIN, static_cast<float>(y) / 2, maxSize, maxSize, LEFT);
        Renderer::drawTriangle(static_cast<float>(x) - GRID_MARGIN - maxSize, static_cast<float>(y) / 2, maxSize,
                               maxSize, RIGHT);

        SDL_Rect leftTriangle{GRID_MARGIN, y / 2, static_cast<int>(maxSize), static_cast<int>(maxSize)};
        SDL_Rect rightTriangle{x - GRID_MARGIN - static_cast<int>(maxSize), y / 2, static_cast<int>(maxSize),
                               static_cast<int>(maxSize)};
        SDL_Rect rectChoose = Renderer::drawButton("Choose", BOTTOM_RIGHT, BLACK, 20, 0);
        SDL_Rect rectGenerateNewGrid = Renderer::drawButton("Generate", BOTTOM_MIDDLE, BLACK);
        SDL_Rect rectBack = Renderer::drawButton("Back", TOP_RIGHT, BLACK);
        SDL_Rect rectMakeOwnGrid = Renderer::drawButton("Create", BOTTOM_LEFT, BLACK);

        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            if (SDL_PointInRect(&mousePosition, &leftTriangle)) {
                --counter;
            }

            if (SDL_PointInRect(&mousePosition, &rightTriangle)) {
                ++counter;
            }

            if (counter < 0) counter = static_cast<int>(grids.size()) - 1;

            if (counter >= static_cast<int>(grids.size())) counter = 0;

            if (SDL_PointInRect(&mousePosition, &rectChoose)) {
                for (auto currentGrid : grids) {
                    if (currentGrid != grids.at(counter))
                    {
                        delete currentGrid;
                    }
                }
                return grids.at(counter);
            }

            if (SDL_PointInRect(&mousePosition, &rectGenerateNewGrid)) {
                grids.push_back(Grid::generateGrid());
                counter = static_cast<int>(grids.size()) - 1;
            }

            if (SDL_PointInRect(&mousePosition, &rectBack)) {
                quit = true;
            }

            if (SDL_PointInRect(&mousePosition, &rectMakeOwnGrid)) {
                Game generateGridGame{};
                Grid *grid = generateGridGame.makeOwnGrid();
                if (grid != nullptr)
                {
                    grids.push_back(grid);
                    counter = static_cast<int>(grids.size()) - 1;
                }
            }
        }

        grids.at(counter)->drawPreview();
        difficulty difficulty = Difficulty::getDifficulty(grids.at(counter));
        if (difficulty == difficulty::easy) Renderer::drawText("Easy", TOP_LEFT, BLACK);
        if (difficulty == difficulty::medium) Renderer::drawText("Medium", TOP_LEFT, BLACK);
        if (difficulty == difficulty::hard) Renderer::drawText("Hard", TOP_LEFT, BLACK);
        SDL_RenderPresent(Renderer::m_renderer);
    }
    for (auto currentGrid : grids) {
        delete currentGrid;
    }
    return nullptr;
}

bool UserInterface::wonGame()
{
    bool quit{false};
    bool playAgain{false};
    SDL_Event event;
    SDL_Point mousePosition{0};
    Renderer::init();

    while (!quit && !m_quit)
    {
        int x;
        int y;
        SDL_GetWindowSize(Renderer::m_window, &x, &y);
        Renderer::fillBackground(BACKGROUND_COLOR);
        Renderer::drawText("Congratulations !", TOP_MIDDLE, RED, 0, 20);
        Renderer::drawText("you won the game !", TOP_MIDDLE, YELLOW, 0, 110);
        Renderer::drawCrown(static_cast<float>(x)/2 - 140, static_cast<float>(y)/2 - 120, 140, 160);

        SDL_Rect rectPlayAgain = Renderer::drawButton("Play Again", BOTTOM_MIDDLE, BLACK);
        SDL_Rect rectExit = Renderer::drawButton("Exit", BOTTOM_RIGHT, RED);

        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            quit = true;
            m_quit = true;
        }

        if (event.type == SDL_MOUSEMOTION) {
            mousePosition = {event.motion.x, event.motion.y};
        }

        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if (SDL_PointInRect(&mousePosition, &rectExit))
            {
                quit = true;
            }

            if (SDL_PointInRect(&mousePosition, &rectPlayAgain))
            {
                showMenu();
                quit = true;
                playAgain = true;
            }
        }

        SDL_RenderPresent(Renderer::m_renderer);
    }
    return playAgain;
}

bool UserInterface::solverMenu(Grid *grid)
{
    bool quit{false};
    bool playAgain{false};
    SDL_Event event;
    SDL_Point mousePosition{0};
    Solver solver;
    Grid solvedGrid = solver.recursiveSolver(*grid);
    bool isSolvable = solvedGrid.checkIfWon();

    while (!quit && !m_quit)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            quit = true;
            m_quit = true;
        }

        if (event.type == SDL_MOUSEMOTION)
        {
            mousePosition = {event.motion.x, event.motion.y};
        }

        Renderer::fillBackground(GRAY);
        if (isSolvable)
        {
            solvedGrid.drawPreview();
            Renderer::drawText("Finished", TOP_MIDDLE, BLACK);
        } else
        {
            Renderer::drawText("This Grid is unsolvable", TOP_MIDDLE, BLACK);
        }

        SDL_Rect rectExit = Renderer::drawButton("EXIT", BOTTOM_RIGHT, RED, 50);
        SDL_Rect rectPlayAgain = Renderer::drawButton("PLAY AGAIN", BOTTOM_MIDDLE, BLACK, 50);

        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if (SDL_PointInRect(&mousePosition, &rectExit))
            {
                quit = true;
            }

            if (SDL_PointInRect(&mousePosition, &rectPlayAgain))
            {
                quit = true;
                playAgain = true;
            }
        }

        SDL_RenderPresent(Renderer::m_renderer);
    }
    return playAgain;
}