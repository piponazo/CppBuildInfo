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
    EXPECT_EQ(static_cast<std::size_t>(0), instance.getTotalTime());
}

TEST(LibCppBuildInfoDataParser, shouldCreateInstanceWithValidDataAndReadValues)
{
    DataParser instance (QString(TEST_DATA_PATH) + "/fakeFile4ConcurrentCompilations.txt");
    EXPECT_FALSE(instance.getAllProcesses().empty());
    EXPECT_EQ(static_cast<std::size_t>(4), instance.getNConcurrentProcesses());

    DataParser instance2 (QString(TEST_DATA_PATH) + "/fakeFile5ConcurrentCompilations.txt");
    EXPECT_FALSE(instance2.getAllProcesses().empty());
    EXPECT_EQ(static_cast<std::size_t>(5), instance2.getNConcurrentProcesses());

    DataParser instance3 (QString(TEST_DATA_PATH) + "/fakeFile6ConcurrentCompilations.txt");
    EXPECT_FALSE(instance3.getAllProcesses().empty());
    EXPECT_EQ(static_cast<std::size_t>(6), instance3.getNConcurrentProcesses());
}
