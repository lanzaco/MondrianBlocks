#include "gtest/gtest.h"
#include "SDL.h"

//Needed to make it work with SDL
int main(int arc, char* argv[])
{
    return 0;
}

TEST(Tests, BasicAssertion)
{
    ASSERT_EQ(3*4, 12);
}