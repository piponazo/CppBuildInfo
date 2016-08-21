#include <CppBuildInfo/DataParser.h>
#include <CppBuildInfo/CompilationProcess.h>
#include <gtest/gtest.h>

#include "tests_config.h"

#include <QFile>
#include <QDir>

TEST(LibCppBuildInfoDataParser, shouldCreateInstanceWithNonExistingFileAndThrowException)
{
    const QString path = QDir::tempPath() + "/NonExistingFile.txt";
    EXPECT_THROW(DataParser instance (path), std::runtime_error);
}

TEST(LibCppBuildInfoDataParser, shouldCreateInstanceWithEmptyFileAndReadNothing)
{
    const QString path = QDir::tempPath() + "/EmptyFile.txt";
    QFile file(path);
    ASSERT_TRUE(file.open(QIODevice::WriteOnly | QIODevice::Text));
    file.close();
    ASSERT_TRUE(QFileInfo::exists(path));

    DataParser instance (path);
    EXPECT_TRUE(instance.getAllProcesses().empty());
    EXPECT_EQ(static_cast<std::size_t>(0), instance.getNConcurrentProcesses());
}

TEST(LibCppBuildInfoDataParser, shouldCreateInstanceWithValidDataAndReadValues)
{
    const QString path = QString(TEST_DATA_PATH) + "/fakeFile8ConcurrentCompilations.txt";
    DataParser instance (path);

    EXPECT_FALSE(instance.getAllProcesses().empty());
    EXPECT_EQ(static_cast<std::size_t>(8), instance.getNConcurrentProcesses());
}

/// \todo make parseData public and returning false if the data in the file is not valid
