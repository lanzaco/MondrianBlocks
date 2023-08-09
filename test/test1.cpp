#include "gtest/gtest.h"
#include "SDL.h"

//Needed to make it work with SDL
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}

TEST(Tests, BasicAssertion)
{
    ASSERT_EQ(3*4, 12);
}