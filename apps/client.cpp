#include <QCoreApplication>
#include <QProcess>
#include <QStringList>
#include <QTime>

#include <iostream>

using namespace std;

int main (int argc, char **argv)
{
    const int maxTimeInMsecs = 30000;
    QCoreApplication app (argc, argv);
    QStringList args = app.arguments();
    cout << "Hello world: Client!" << endl;
    cout << "N Args: " << argc << endl;
    args.removeFirst();
    QString argsTogeter = args.join(" ");
    cout << "Args: " << argsTogeter.toStdString() << endl;

    QProcess process;
    process.setProcessChannelMode(QProcess::ForwardedChannels);

    QTime startTime = QTime::currentTime();
    process.start(argsTogeter);
    if (process.waitForFinished(maxTimeInMsecs) == false) {
        cerr << "application timeout" << endl;

    }
    QTime endTime = QTime::currentTime();

    cout << "Application finished correctly" << endl;
    cout << "Time: " << startTime.msecsTo(endTime) << "msecs" << endl;
    // The idea for the client application would be the following (idea taken from GNU time command):
    // - Parse the command line
    // - Start the measure
    // - Run command (Use QProcess with the objective to be platform independent)
    // - Stop the measure
}
