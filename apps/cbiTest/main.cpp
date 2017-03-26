/* Test application to quickly check the final CBI application with data files.
 */

#include <QProcess>
#include <QStringList>
#include <QDateTime>
#include <QTextStream>
#include <QFile>
#include <QDebug>

#include <iostream>

using namespace std;

static QString outputFile;
static QString sourceFile;

int main (int argc, char **argv)
{
    if (argc != 3 || QString(argv[1]) != "-i") {
        std::cerr << "Syntaxis: appName -i inputFile" << std::endl;
        return EXIT_FAILURE;
    }

    QFile inputFile(argv[2]);
    if (!inputFile.open(QFile::ReadOnly | QFile::Text)) {
        std::cerr << "Fail opening file" << std::endl;
        return EXIT_FAILURE;
    }

    QTextStream streamer(&inputFile);
    QString line;
    while (!streamer.atEnd()) {
        line = streamer.readLine();
    }

    return EXIT_SUCCESS;
}
