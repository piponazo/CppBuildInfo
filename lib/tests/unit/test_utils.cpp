#include <CppBuildInfo/DataParser.h>
#include <CppBuildInfo/utils.h>

#include "../gtestWrapper.h"

#include "tests_config.h"

TEST(maximumNumberOfParallelCompilations, detectsParallelProcesses)
{
    DataParser parser;
    parser.parse(QString(TEST_DATA_PATH) + "/fakeFile4ConcurrentCompilations.txt");
    EXPECT_EQ(4, maximumNumberOfParallelCompilations(parser.getAllProcesses()));

    parser.parse(QString(TEST_DATA_PATH) + "/fakeFile5ConcurrentCompilations.txt");
    EXPECT_EQ(5, maximumNumberOfParallelCompilations(parser.getAllProcesses()));

    parser.parse(QString(TEST_DATA_PATH) + "/fakeFile6ConcurrentCompilations.txt");
    EXPECT_EQ(6, maximumNumberOfParallelCompilations(parser.getAllProcesses()));
}

TEST(maximumNumberOfParallelCompilations, gets0WithEmptyVector)
{
    EXPECT_EQ(0, maximumNumberOfParallelCompilations({}));
}
