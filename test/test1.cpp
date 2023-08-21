#include "gtest/gtest.h"

//Needed to make it work with SDL
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    (void) RUN_ALL_TESTS();

    return 0;
}