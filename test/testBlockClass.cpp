#include "gtest/gtest.h"
#include "../src/Blocks.hpp"


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


