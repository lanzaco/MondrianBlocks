#include "gtest/gtest.h"
#include "../src/Blocks.hpp"
#include "../src/Colors.hpp"

/*
 class GameTest : public::testing::Test
{
protected:
    Game m_game;
    virtual void SetUp() override
    {
        m_game = Game();
    }
    void rollOnlyThisNumber(int rolls, int pins)
    {
        for (int i = 0; i < rolls; ++i)
        {
            m_game.roll(pins);
        }
    }
};

TEST_F(GameTest, ScoreIsZeroWithOnlyZeroRolls)
{
    rollOnlyThisNumber(20,0);
    EXPECT_EQ(m_game.getScore(), 0);
}
 */

class BlockClassTest : public::testing::Test
{
protected:
    Blocks m_block{};
    void SetUp() override
    {
        m_block = Blocks();
        m_block.setRotate(false);
    }
};

TEST_F(BlockClassTest, TestRotate)
{
    bool beforeRotation = m_block.getIsRotated();
    m_block.rotate();
    bool afterRotation = m_block.getIsRotated();
    EXPECT_EQ(beforeRotation, !afterRotation);
}


