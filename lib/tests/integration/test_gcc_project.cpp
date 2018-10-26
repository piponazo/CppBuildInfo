#include <CppBuildInfo/CompilerParserFactory.h>

#include "../gtestWrapper.h"

#include "tests_config.h"

#include <QFile>
#include <QTextStream>

TEST(AnalyzeGccProject, obtainValidProjectModel)
{
    QString exiv2Sample(QString(TEST_DATA_PATH) + "/exiv2_gcc_linux.txt");
    QFile file(exiv2Sample);
    ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream stream (&file);

    auto parser = createParser(CompilerType::GCC);
    ProjectModel model;

    while (!stream.atEnd()) {
        auto line = stream.readLine();
        auto unit = parser->parse(line, model);
    }

    ASSERT_EQ(168, model.units.size());
}
