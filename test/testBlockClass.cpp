#include "gtest/gtest.h"
#include "../src/Blocks.hpp"

class BlockClassTest : public ::testing::Test
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
    ASSERT_EQ(beforeRotation, !afterRotation);
}

TEST_F(BlockClassTest, AreHightAndWidthSwapped)
{
    int heightBeforeRotation = m_block.getRect()->h;
    int widthBeforeRotation = m_block.getRect()->w;
    m_block.rotate();
    ASSERT_EQ(heightBeforeRotation, m_block.getRect()->w);
    ASSERT_EQ(widthBeforeRotation, m_block.getRect()->h);
}

TEST_F(BlockClassTest, GetNewCoords)
{
    int x;
    int y;
    m_block.setX(1);
    m_block.setY(1);
    m_block.updateRect();
    std::tie(x, y) = m_block.getNewCoords();
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 1);
}
