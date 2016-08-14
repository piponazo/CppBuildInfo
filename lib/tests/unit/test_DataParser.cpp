#include <CppBuildInfo/DataParser.h>
#include <gtest/gtest.h>

#include <QFile>

class LibCppBuildInfoDataParserEmptyFile : public ::testing::Test
{
protected:
    static void SetUpTestCase()
    {
        // Create empty file
    }

    static void TearDownTestCase()
    {
        // Remove the file
    }

    void SetUp()
    {
    }

    void TearDown()
    {
    }

    QString file;
};

TEST_F(LibCppBuildInfoDataParserEmptyFile, shouldCreateInstance)
{
    DataParser instance (file);
}
