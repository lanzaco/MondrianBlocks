#include "gtest/gtest.h"
#include "../src/Grid.hpp"
#include "../src/Colors.hpp"
#include "../src/Difficulty.hpp"

#include <vector>
#include <algorithm>

constexpr int MAXCOLUMN = 7;

class TestDifficultyClass : public ::testing::Test
{
protected:
    Grid m_grid{};

    static Grid setUpEasyGrid()
    {
        std::vector<Blocks *> easyBlocks = {};
        easyBlocks.push_back(new Blocks{2, 3, 1, 2, BLACK, false});
        easyBlocks.push_back(new Blocks{5, 6, 1, 1, BLACK, false});
        easyBlocks.push_back(new Blocks{4, 2, 1, 3, BLACK, false});
        Grid easyGrid{easyBlocks};
        return easyGrid;
    }
    static Grid setUpMediumGrid()
    {
        std::vector<Blocks *> mediumBlocks = {};
        mediumBlocks.push_back(new Blocks{7, 1, 1, 1, BLACK, false});
        mediumBlocks.push_back(new Blocks{5, 2, 1, 2, BLACK, false});
        mediumBlocks.push_back(new Blocks{2, 4, 3, 1, BLACK, false});
        Grid mediumGrid{mediumBlocks};
        return mediumGrid;
    }
    static Grid setUpHardGrid()
    {
        std::vector<Blocks *> hardBlocks = {};
        hardBlocks.push_back(new Blocks{0, 2, 1, 1, BLACK, false});
        hardBlocks.push_back(new Blocks{5, 2, 1, 2, BLACK, false});
        hardBlocks.push_back(new Blocks{2, 4, 3, 1, BLACK, false});
        Grid hardGrid{hardBlocks};
        return hardGrid;
    }
    static Grid setUpImpossibleGrid()
    {
        std::vector<Blocks *> impossibleBlocks = {};
        impossibleBlocks.push_back(new Blocks{1, 1, 1, 1, BLACK, false});
        impossibleBlocks.push_back(new Blocks{3, 2, 1, 2, BLACK, false});
        impossibleBlocks.push_back(new Blocks{1, 5, 3, 1, BLACK, false});
        Grid impossibleGrid{impossibleBlocks};
        return impossibleGrid;
    }
};
// function: getDifficulty()

TEST_F(TestDifficultyClass, GetDifficultyEasy)
{
    m_grid = setUpEasyGrid();
    ASSERT_EQ(difficulty::easy, Difficulty::getDifficulty(&m_grid));
}

TEST_F(TestDifficultyClass, GetDifficultyMedium)
{
    m_grid = setUpMediumGrid();
    ASSERT_EQ(difficulty::medium, Difficulty::getDifficulty(&m_grid));
}

TEST_F(TestDifficultyClass, GetDifficultyHard)
{
    m_grid = setUpHardGrid();
    ASSERT_EQ(difficulty::hard, Difficulty::getDifficulty(&m_grid));
}

TEST_F(TestDifficultyClass, GetDifficultyImpossible)
{
    m_grid = setUpImpossibleGrid();
    ASSERT_EQ(difficulty::impossible, Difficulty::getDifficulty(&m_grid));
}