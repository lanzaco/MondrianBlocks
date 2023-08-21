#include "gtest/gtest.h"
#include "SDL.h"

//Needed to make it work with SDL
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();

    return result;
}