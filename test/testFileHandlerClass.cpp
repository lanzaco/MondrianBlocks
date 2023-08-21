#include "gtest/gtest.h"
#include "../src/FileHandler.hpp"

class FileHandlerTest : public::testing::Test
{
protected:
    FileHandler m_fileHandler{};
};

TEST_F(FileHandlerTest, TestSizeOfGridList)
{
    ASSERT_EQ(6, m_fileHandler.readFile("./../../data/data_file.txt").size());
}

TEST_F(FileHandlerTest, TestSizeOfGridListEmptyFile)
{
    ASSERT_EQ(0, m_fileHandler.readFile("./../../data/empty_file.txt").size());
}

TEST_F(FileHandlerTest, TestGridSizeEmptyFile)
{
    m_fileHandler.readFile("./../../data/empty_file.txt");
    ASSERT_EQ(8, Grid::getGridSize());
}

TEST_F(FileHandlerTest, TestSizeOfGridListWrongPath)
{
    ASSERT_EQ(0,m_fileHandler.readFile("./../../wrong_path.txt").size());
}

TEST(FileHandlerTest_2, TestSetGridSize)
{
    FileHandler fileHandler{};
    fileHandler.readFile("./../../data/file_setsGridSizeTo_7.txt");
    ASSERT_EQ(7, Grid::getGridSize());
    // has to be set back to 8 for the following tests
    Grid::setGridSize(8);
}

