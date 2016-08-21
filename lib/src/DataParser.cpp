#include <CppBuildInfo/DataParser.h>
#include <CppBuildInfo/CompilationProcess.h>

#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QTime>

#include <QDebug>

#include <algorithm>

// -------------------------------------------------------------------------------------------------
// Private implementation details
// -------------------------------------------------------------------------------------------------
namespace {
    void processCompilationProcess(const CompilationProcess &proc, std::vector<CompilationProcess> &procs)
    {
        if (!procs.empty() && procs.back().end < proc.start) {
            procs.pop_back();
        }
        procs.push_back(proc);
        std::sort(procs.begin(), procs.end());
    }
}

/// \todo remove data duplication once we know what we really want ^_^u

struct DataParser::Pimpl
{
    Pimpl (const QString &path)
        : file(path)
        , maxProcs(0)
    {
    }

    QFile           file;

    QStringList     fileNames;
    QList<qint64>   times;
    QList<qint64>   starting;
    QList<qint64>   ending;
    std::size_t     maxProcs;
};


// -------------------------------------------------------------------------------------------------
// Public class methods
// -------------------------------------------------------------------------------------------------

DataParser::DataParser(const QString &path)
    : _impl(nullptr)
{
    if (!QFileInfo::exists(path))
    {
        throw std::runtime_error("File does not exist: " + path.toStdString());
    }

    _impl = new Pimpl(path);
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

const QList<qint64> & DataParser::getTimes() const
{
    return _impl->times;
}

const QList<qint64> &DataParser::getStartingTimes() const
{
    return _impl->starting;
}

const QList<qint64> &DataParser::getEndingTimes() const
{
    return _impl->ending;
}

int DataParser::getNComcurrentProcesses() const
{
    return 0;
}

// -------------------------------------------------------------------------------------------------
// Private class methods
// -------------------------------------------------------------------------------------------------

bool DataParser::parseData()
{
    if (!_impl->file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error opening file";
        return false;
    }
    QTextStream stream (&_impl->file);

    QTime aux;
    QString line, absolutePath, fileName;
    QStringList tokens;
    bool ok1 = true, ok2 = true, ok3 = true;
    qint64 msecs, start, end;
    quint32 lineNumber = 0;

    std::vector<CompilationProcess> procs;

    while (!stream.atEnd()) {
        line = stream.readLine();
        tokens = line.split(" ");

        absolutePath = tokens.at(0);
        const int idxLastSlash = absolutePath.lastIndexOf('/');
        fileName = absolutePath.mid(idxLastSlash + 1);

        msecs = tokens.at(1).toLong(&ok1);
        start = tokens.at(2).toLong(&ok2);
        end = tokens.at(3).toLong(&ok3);

        if (!ok1 || !ok2 || !ok3) {
            qWarning() << "Error parsing line" << lineNumber;
            return false;
        } else {
            _impl->fileNames << fileName;
            _impl->times << msecs;
            _impl->starting << start;
            _impl->ending << end;
            CompilationProcess proc(fileName, start, end);
            processCompilationProcess(proc, procs);
            _impl->maxProcs = std::max(_impl->maxProcs, procs.size());
        }

        lineNumber++;
    }
    return true;
}
