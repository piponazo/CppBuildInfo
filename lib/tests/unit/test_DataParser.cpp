#include <CppBuildInfo/DataParser.h>
#include <CppBuildInfo/TranslationUnit.h>
#include <CppBuildInfo/utils.h>

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
    EXPECT_EQ(21, parser.getAllProcesses().size());
}
