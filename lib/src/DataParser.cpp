#include <CppBuildInfo/DataParser.h>

#include <QFile>
#include <QTextStream>
#include <QTime>

#include <QDebug>

/// \todo remove data duplication once we know what we really want ^_^u
///
/// \note Idea: Create another class to contain all the information related with a compilation unit:
/// - library / application
/// - time
/// - ...

struct DataParser::Pimpl
{
    Pimpl (const QString &path)
        : file(path)
    {
    }

    QFile       file;

    QStringList fileNames;
    QList<int> times;
    QList<int> starting;
    QList<int> ending;
};

DataParser::DataParser(const QString &path)
    : _impl(new Pimpl(path))
{
    parseData();
}

DataParser::~DataParser()
{
    delete _impl;
}

const QStringList & DataParser::getFileNames() const
{
    return _impl->fileNames;
}

const QList<int> & DataParser::getTimes() const
{
    return _impl->times;
}

const QList<int> &DataParser::getStartingTimes() const
{
    return _impl->starting;
}

const QList<int> &DataParser::getEndingTimes() const
{
    return _impl->ending;
}

bool DataParser::parseData()
{
    if (!_impl->file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error opening file";
        return false;
    }
    QTextStream stream (&_impl->file);
    const QString timeFormat("hh:mm:ss.zzz");

    QTime aux;
    QString line, absolutePath, fileName;
    QStringList tokens;
    bool ok = true;
    int msecs;
    quint32 lineNumber = 0;

    while (!stream.atEnd()) {
        line = stream.readLine();
        tokens = line.split(" ");

        absolutePath = tokens.at(0);
        const int idxLastSlash = absolutePath.lastIndexOf('/');
        fileName = absolutePath.mid(idxLastSlash + 1);

        msecs = tokens.at(1).toInt(&ok);

        QTime startTime = QTime::fromString(tokens.at(2), timeFormat);
        QTime endTime = QTime::fromString(tokens.at(2), timeFormat);
        /// \todo use msecs from epoch instead

        if (ok == false) {
            qWarning() << "Error parsing line" << lineNumber;
        } else {
            _impl->times << msecs;
            _impl->fileNames << fileName;
            _impl->starting << startTime.msecsSinceStartOfDay();
            _impl->ending << endTime.msecsSinceStartOfDay();
        }

        lineNumber++;
    }
    return true;
}
