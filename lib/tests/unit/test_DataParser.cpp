#include <CppBuildInfo/DataParser.h>
#include <CppBuildInfo/TranslationUnit.h>

#include "../gtestWrapper.h"

#include "tests_config.h"

#include <QFile>
#include <QDir>

namespace
{
    QString createEmptyFile(const QString fileName)
    {
        const QString path (QDir::tempPath() + "/" + fileName);
        QFile file(path);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.close();
        return path;
    }
}

TEST(ADataParser, parseReturnsFalseWithNonExistingFile)
{
    const QString path (QDir::tempPath() + "/NonExistingFile.txt");
    DataParser parser;
    ASSERT_FALSE(parser.parse(path));
}

TEST(ADataParser, parseCorrectlyEmptyFile)
{
    auto path = createEmptyFile("EmptyFile.txt");
    ASSERT_TRUE(QFile::exists(path));

    DataParser parser;
    ASSERT_TRUE(parser.parse(path));
    EXPECT_TRUE(parser.getAllProcesses().empty());
    EXPECT_EQ(static_cast<std::size_t>(0), parser.getNConcurrentProcesses());
    EXPECT_EQ(static_cast<std::size_t>(0), parser.getTotalTime());
}

TEST(ADataParser, failToParseFilesWithBadFormat)
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
