#include <CppBuildInfo/DataParser.h>
#include <CppBuildInfo/CompilationProcess.h>
#include <gtest/gtest.h>

#include "tests_config.h"

#include <QFile>
#include <QDir>

TEST(ADataParser, doNotParseNonExistingFile)
{
    const QString path (QDir::tempPath() + "/NonExistingFile.txt");
    DataParser parser;
    ASSERT_FALSE(parser.parse(path));
}

TEST(ADataParser, doNotDetectProcessesInEmptyFile)
{
    const QString path (QDir::tempPath() + "/EmptyFile.txt");
    QFile file(path);
    ASSERT_TRUE(file.open(QIODevice::WriteOnly | QIODevice::Text));
    file.close();
    ASSERT_TRUE(QFile::exists(path));

    DataParser parser;
    ASSERT_TRUE(parser.parse(path));
    EXPECT_TRUE(parser.getAllProcesses().empty());
    EXPECT_EQ(static_cast<std::size_t>(0), parser.getNConcurrentProcesses());
    EXPECT_EQ(static_cast<std::size_t>(0), parser.getTotalTime());
}

TEST(ADataParser, doNotDetectProcessesInFilesWithBadFormat)
{
    DataParser parser;
    ASSERT_FALSE(parser.parse(QString(TEST_DATA_PATH) + "/badFileWithLessFieldsPerLine.txt"));
    ASSERT_FALSE(parser.parse(QString(TEST_DATA_PATH) + "/badFileWithMoreFieldsPerLine.txt"));
    ASSERT_FALSE(parser.parse(QString(TEST_DATA_PATH) + "/badFileWithBadTypes.txt"));
}

TEST(ADataParser, detectProcessesInNonProperEmptyFiles)
{
    DataParser parser;
    parser.parse(QString(TEST_DATA_PATH) + "/fakeFile4ConcurrentCompilations.txt");
    EXPECT_FALSE(parser.getAllProcesses().empty());
    EXPECT_EQ(std::size_t(4), parser.getNConcurrentProcesses());

    parser.parse(QString(TEST_DATA_PATH) + "/fakeFile5ConcurrentCompilations.txt");
    EXPECT_FALSE(parser.getAllProcesses().empty());
    EXPECT_EQ(std::size_t(5), parser.getNConcurrentProcesses());

    parser.parse(QString(TEST_DATA_PATH) + "/fakeFile6ConcurrentCompilations.txt");
    EXPECT_FALSE(parser.getAllProcesses().empty());
    EXPECT_EQ(std::size_t(6), parser.getNConcurrentProcesses());
}
