#include "gtest/gtest.h"
#include "../src/Grid.hpp"
#include "../src/Colors.hpp"
#include "../src/Difficulty.hpp"

#include <vector>

constexpr int MAXCOLUMN = 7;

class TestGridClass : public::testing::Test
{
protected:
    Grid m_grid{};

    Blocks m_newBlock{0,0,1,1,BLACK, false};

    bool isGridEmpty()
    {
        auto grid = *m_grid.getGrid();
        return std::all_of(grid.cbegin(), grid.cend(), [](Blocks* block){ return block == nullptr;});
    };
    void setUpClearTest()
    {
        m_grid = Grid();
        m_grid.placeBlock(new Blocks(0, 0, 1, 1, BLACK));
    };
    void placeEmptyListOfBlocks()
    {
        std::vector<Blocks*> emptyVecBlocks = {};
        for(auto currentBlock : emptyVecBlocks)
        {
            m_grid.placeBlock(currentBlock);
        }
    }
    void setUpFullGrid()
    {
        for(int positionGrid = 0; positionGrid < Grid::getGridSize() * Grid::getGridSize(); ++positionGrid)
        {
            m_grid.getGrid()->at(positionGrid) = m_grid.getNotPlacedBlocks()->front();
        }
    }
    static Grid setUpEasyGrid()
    {
        std::vector<Blocks*> easyBlocks = {};
        easyBlocks.push_back(new Blocks{2,3,1,2,BLACK, false});
        easyBlocks.push_back(new Blocks{5,6,1,1,BLACK, false});
        easyBlocks.push_back(new Blocks{4,2,1,3,BLACK, false});
        Grid easyGrid{easyBlocks};
        return easyGrid;
    }
    static Grid setUpMediumGrid()
    {
        std::vector<Blocks*> mediumBlocks = {};
        mediumBlocks.push_back(new Blocks{7,1,1,1,BLACK, false});
        mediumBlocks.push_back(new Blocks{5,2,1,2,BLACK, false});
        mediumBlocks.push_back(new Blocks{2,4,3,1,BLACK, false});
        Grid mediumGrid{mediumBlocks};
        return mediumGrid;
    }
    static Grid setUpHardGrid()
    {
        std::vector<Blocks*> hardBlocks = {};
        hardBlocks.push_back(new Blocks{0,2,1,1,BLACK, false});
        hardBlocks.push_back(new Blocks{5,2,1,2,BLACK, false});
        hardBlocks.push_back(new Blocks{2,4,3,1,BLACK, false});
        Grid hardGrid{hardBlocks};
        return hardGrid;
    }
    static Grid setUpImpossibleGrid()
    {
        std::vector<Blocks*> impossibleBlocks = {};
        impossibleBlocks.push_back(new Blocks{1,1,1,1,BLACK, false});
        impossibleBlocks.push_back(new Blocks{3,2,1,2,BLACK, false});
        impossibleBlocks.push_back(new Blocks{1,5,3,1,BLACK, false});
        Grid impossibleGrid{impossibleBlocks};
        return impossibleGrid;
    }
};

TEST_F(TestGridClass, testClearFunction)
{
    setUpClearTest();
    m_grid.clear();
    for(auto iterator : *m_grid.getGrid())
    {
        ASSERT_EQ(nullptr, iterator);
    }
}

//function: checkIfPlaceable()

TEST_F(TestGridClass, TryToPlaceOneBlock)
{
    ASSERT_TRUE(m_grid.checkIfPlaceable(&m_newBlock));
}

TEST_F(TestGridClass, TryToPlaceSameBlockTwice)
{
    m_grid.placeBlock(&m_newBlock);
    ASSERT_TRUE(m_grid.checkIfPlaceable(&m_newBlock));
}

TEST_F(TestGridClass, TryToPlaceTwoDifferentBlocksAtTheSamePlace)
{
    Blocks differentBlock{0,0,1,1,BLACK, false};
    m_grid.placeBlock(&m_newBlock);
    ASSERT_FALSE(m_grid.checkIfPlaceable(&differentBlock));
}

TEST_F(TestGridClass, TryToPlaceTwoBlocksAtDifferentPlaces)
{
    Blocks firstBlock{0,0,1,1,BLACK, false};
    Blocks secondBlock{2,2,1,1,BLACK, false};

    m_grid.placeBlock(&firstBlock);
    ASSERT_TRUE(m_grid.checkIfPlaceable(&secondBlock));
}

TEST_F(TestGridClass, TryToPlaceABlockOutsideTheGrid)
{
    Blocks outsideOfGridBlock{MAXCOLUMN, MAXCOLUMN, 2,2, BLACK, false};
    ASSERT_FALSE(m_grid.checkIfPlaceable(&outsideOfGridBlock));
}

TEST_F(TestGridClass, TryToPlaceBlockIntoFullGrid)
{
    setUpFullGrid();
    ASSERT_FALSE(m_grid.checkIfPlaceable(&m_newBlock));
}

//function: placeBlock()

TEST_F(TestGridClass, PlacedBlockIsAnElementOfBlocksVector)
{
    m_grid.placeBlock(&m_newBlock);
    ASSERT_FALSE(isGridEmpty());
    ASSERT_EQ(1, m_grid.getBlocks()->size());
}

TEST_F(TestGridClass, PlaceEmptyListOfBlocks)
{
    placeEmptyListOfBlocks();
    ASSERT_TRUE(isGridEmpty());
    ASSERT_EQ(0, m_grid.getBlocks()->size());
}

TEST_F(TestGridClass, CheckIfNotPlacedBlocksDecreases)
{
    unsigned long countNotPlacedBlocks = m_grid.getNotPlacedBlocks()->size();
    m_grid.placeBlock(m_grid.getNotPlacedBlocks()->front());
    ASSERT_EQ(countNotPlacedBlocks - 1, m_grid.getNotPlacedBlocks()->size());
}

TEST_F(TestGridClass, PlaceSameBlockTwice)
{

    Blocks* block = m_grid.getNotPlacedBlocks()->front();
    m_grid.placeBlock(block);
    m_grid.placeBlock(m_grid.getBlocks()->back());
    ASSERT_EQ(1, m_grid.getBlocks()->size());

}

//function: removeBlock()

TEST_F(TestGridClass, NumberOfPlacedBlocksIncreases)
{
    Blocks* placedBlock = m_grid.getNotPlacedBlocks()->front();
    m_grid.placeBlock(placedBlock);
    unsigned long countNotPlacedBlocks = m_grid.getNotPlacedBlocks()->size();
    m_grid.removeBlock(placedBlock);
    ASSERT_EQ(countNotPlacedBlocks + 1, m_grid.getNotPlacedBlocks()->size());
}

TEST_F(TestGridClass, NumberofPlacedBlocksDecreases)
{
    Blocks* placedBlock = m_grid.getNotPlacedBlocks()->front();
    m_grid.placeBlock(placedBlock);
    m_grid.removeBlock(placedBlock);
    ASSERT_EQ(0, m_grid.getBlocks()->size());
}

TEST_F(TestGridClass, RemoveBlockThatIsNotInTheGrid)
{
    m_grid.placeBlock(m_grid.getNotPlacedBlocks()->back());
    m_grid.removeBlock(m_grid.getNotPlacedBlocks()->front());
    ASSERT_EQ(1, m_grid.getBlocks()->size());
}

// function: moveBlock()

TEST_F(TestGridClass, MoveBlockInTheGridThatIsPlaceable)
{
    m_grid.placeBlock(m_grid.getNotPlacedBlocks()->front());
    Blocks* placedBlock = m_grid.getBlocks()->back();
    placedBlock->setX(3);
    placedBlock->setY(0);
    unsigned long countNotPlacedBlocks = m_grid.getNotPlacedBlocks()->size();
    m_grid.moveBlock(placedBlock);
    ASSERT_EQ(countNotPlacedBlocks, m_grid.getNotPlacedBlocks()->size());
}

TEST_F(TestGridClass, MoveBlockOutOfTheGrid)
{
    m_grid.placeBlock(m_grid.getNotPlacedBlocks()->front());
    Blocks* placedBlock = m_grid.getBlocks()->back();
    placedBlock->setX(MAXCOLUMN + 1);
    placedBlock->setY(MAXCOLUMN + 1);
    placedBlock->updateRect();
    m_grid.moveBlock(placedBlock);
    ASSERT_EQ(0, m_grid.getBlocks()->size());
}

// function: checkWin()

TEST_F(TestGridClass, CheckWinEmptyGrid)
{
    ASSERT_FALSE(m_grid.checkIfWon());
}

TEST_F(TestGridClass, CheckWinFullGrid)
{
    setUpFullGrid();
    ASSERT_TRUE(m_grid.checkIfWon());
}

//function: gridContainsBlock()

TEST_F(TestGridClass, CheckBlockThatIsInGrid)
{
    Blocks blockInGrid{0,0,1,1,BLACK, false};
    m_grid.placeBlock(&blockInGrid);
    ASSERT_TRUE(m_grid.gridContainsBlock(&blockInGrid));
}

TEST_F(TestGridClass, CheckBlockThatIsNotInGrid)
{
    Blocks blockNotInGrid{0,0,1,1,BLACK, false};
    ASSERT_FALSE(m_grid.gridContainsBlock(&blockNotInGrid));
}

//function: getDifficulty()

TEST_F(TestGridClass, GetDifficultyEasy)
{
    m_grid = setUpEasyGrid();
    ASSERT_EQ(difficulty::easy, Difficulty::getDifficulty(&m_grid));
}

TEST_F(TestGridClass, GetDifficultyMedium)
{
    m_grid = setUpMediumGrid();
    ASSERT_EQ(difficulty::medium, Difficulty::getDifficulty(&m_grid));
}

TEST_F(TestGridClass, GetDifficultyHard)
{
    m_grid = setUpHardGrid();
    ASSERT_EQ(difficulty::hard, Difficulty::getDifficulty(&m_grid));
}

TEST_F(TestGridClass, GetDifficultyImpossible)
{
    m_grid = setUpImpossibleGrid();
    ASSERT_EQ(difficulty::impossible, Difficulty::getDifficulty(&m_grid));
}







