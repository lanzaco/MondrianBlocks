#include "gtest/gtest.h"
#include "../src/Solver.hpp"
#include "../src/Colors.hpp"
#include <vector>

Grid setUpUnsolvableGrid()
{
    std::vector<Blocks*> vecBlocks;
    vecBlocks.push_back(new Blocks(2, 2, 1, 2, BLACK, false));
    vecBlocks.push_back(new Blocks(4, 2, 1, 3, BLACK, false));
    vecBlocks.push_back(new Blocks(0, 0, 1, 1, BLACK, false));
    Grid unsolvableGrid{vecBlocks};
    return unsolvableGrid;
}

Grid setUpSolvableGrid()
{
    std::vector<Blocks*> vecBlocks;
    vecBlocks.push_back(new Blocks(2,3,1,2, BLACK, false));
    vecBlocks.push_back(new Blocks(5,6,1,1, BLACK, false));
    vecBlocks.push_back(new Blocks(4,2,1,3, BLACK, false));
    Grid solvableGrid{vecBlocks};
    return solvableGrid;
}

TEST(Test, SolvableGrid)
{
    Solver solver{};
    Grid grid = setUpSolvableGrid();
    ASSERT_TRUE(solver.recursiveSolver(grid).checkIfWon());
}

TEST(Test, UnsolvableGrid)
{
    Solver solver{};
    Grid grid = setUpUnsolvableGrid();
    ASSERT_FALSE(solver.recursiveSolver(grid).checkIfWon());
}



