#include "gtest/gtest.h"
#include "../src/Grid.hpp"
#include "../src/Colors.hpp"
#include <vector>

class TestGridClass : public::testing::Test
{
protected:
    Grid m_grid{};
    std::vector<Blocks*> m_blocks = {};

    void SetUpEmptyListOfBlocks()
    {
        m_grid = Grid(m_blocks);
    }

};

TEST_F(TestGridClass, testClearFunction)
{
    Blocks newBlock(0,0,1,1,BLACK, false);
    m_blocks.push_back(&newBlock);
    m_grid = Grid(m_blocks);
    m_grid.clear();
    for(int currentPosition = 0; currentPosition < Grid::getGridSize() * Grid::getGridSize(); ++currentPosition)
    {
        ASSERT_EQ(nullptr, m_grid.getGrid()->at(currentPosition));
    }
}