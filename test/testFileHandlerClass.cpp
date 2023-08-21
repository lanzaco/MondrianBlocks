#include "gtest/gtest.h"
#include "../src/FileHandler.hpp"

class FileHandlerTest : public ::testing::Test
{
protected:
    FileHandler m_fileHandler{};
};

TEST_F(FileHandlerTest, TestSizeOfGridList)
{
#if _MSC_VER && !__INTEL_COMPILER
    const char filePath[] = "./../data_file.txt";
#else
    const char filePath[] = "./data_file.txt";
#endif
    ASSERT_EQ(6, m_fileHandler.readFile(filePath).size());
}

TEST_F(FileHandlerTest, TestSizeOfGridListEmptyFile)
{
#if _MSC_VER && !__INTEL_COMPILER
    const char filePath[] = "./../empty_file.txt";
#else
    const char filePath[] = "./empty_file.txt";
#endif
    ASSERT_EQ(0, m_fileHandler.readFile(filePath).size());
}

TEST_F(FileHandlerTest, TestGridSizeEmptyFile)
{
#if _MSC_VER && !__INTEL_COMPILER
    const char filePath[] = "./../empty_file.txt";
#else
    const char filePath[] = "./empty_file.txt";
#endif
    m_fileHandler.readFile(filePath);
    ASSERT_EQ(8, Grid::getGridSize());
}

TEST_F(FileHandlerTest, TestSizeOfGridListWrongPath)
{
    ASSERT_EQ(0, m_fileHandler.readFile("./wrong_path.txt").size());
}

TEST(FileHandlerTest_2, TestSetGridSize)
{
#if _MSC_VER && !__INTEL_COMPILER
    const char filePath[] = "./../file_setsGridSizeTo_7.txt";
#else
    const char filePath[] = "./file_setsGridSizeTo_7.txt";
#endif
    FileHandler fileHandler{};
    fileHandler.readFile(filePath);
    ASSERT_EQ(7, Grid::getGridSize());
    // has to be set back to 8 for the following tests
    Grid::setGridSize(8);
}
