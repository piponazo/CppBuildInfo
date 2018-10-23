/* This application append a line into the --outputFile with the following format:
 *
 * AbsolutePathToSourceFile.cpp msecsFromEpochInit msecsFromEpochEnd
 *
 */

#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QProcess>
#include <QStringList>
#include <QTextStream>

#include <iostream>

using namespace std;

static bool parseCommandLineArguments(QStringList &args, QString& outputFile);
static QString getSourceFile(const QStringList &chunks);

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("cbi");
    QCoreApplication::setApplicationVersion("0.0.1");  /// \todo use version set in CMake

    QStringList args = app.arguments();

    QString outputFile;
    if (!parseCommandLineArguments(args, outputFile)) {
        cerr << "Application did not measure times of any command\n";
        return EXIT_FAILURE;
    }

    QString sourceFile = getSourceFile(args);
    QString argsTogeter = args.join(" ");

    QProcess process;
    process.setProcessChannelMode(QProcess::SeparateChannels);

    const int maxTimeInMsecs = 30000;
    qint64 startTime = QDateTime::currentMSecsSinceEpoch();
    process.start(argsTogeter);
    if (process.waitForFinished(maxTimeInMsecs) == false) {
        cerr << "application timeout: " << process.errorString().toStdString() << endl;
        return EXIT_FAILURE;
    }
    qint64 endTime = QDateTime::currentMSecsSinceEpoch();

    if (outputFile.isEmpty()) {
        cout << "Application finished correctly in " << endTime - startTime << " msecs" << endl;
    } else {
        QFile data(outputFile);
        if (data.open(QFile::WriteOnly | QFile::Append)) {
            QTextStream out(&data);
            out << sourceFile << " " << startTime << " " << endTime << endl;
        } else {
            cerr << "Could not open output file " << outputFile.toStdString() << endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

static bool parseCommandLineArguments(QStringList &args, QString& outputFile)
{
    args.removeFirst();  // The first argument is this own application

    if (args.empty() || args.indexOf("-h") != -1 || args.indexOf("--help") != -1) {
        cout << "Syntax: appBinary 'compiler_command_to_be_analyzed' --outputFile fileName\n";
        return false;
    }

    qDebug() << "Inputs args" << args;
    const int indexOutputFile = args.indexOf("--outputFile");
    if (indexOutputFile != -1) {
        outputFile = args.at(indexOutputFile + 1);
        args.erase(args.begin() + indexOutputFile, args.begin() + (indexOutputFile + 2));
    }

    qDebug() << "Output args" << args;
    return true;
}

static QString getSourceFile(const QStringList &chunks)
{
    int indexSourceFile = chunks.indexOf("-c");
    return chunks.at(indexSourceFile + 1);
}
