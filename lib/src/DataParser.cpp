#include <CppBuildInfo/DataParser.h>
#include <CppBuildInfo/CompilationProcess.h>

#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QTime>

#include <QDebug>

#include <algorithm>
#include <functional>

// -------------------------------------------------------------------------------------------------
// Private implementation details
// -------------------------------------------------------------------------------------------------

struct DataParser::Pimpl
{
    Pimpl (const QString &path)
        : file(path)
        , maxProcs(0)
    {
    }

    void processCompilationProcess(const QString &path, const qint64 start, const qint64 end);

    QFile           file;

    std::vector<CompilationProcess> allProcs;
    std::vector<CompilationProcess> concurrentProcs;
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

const std::vector<CompilationProcess> DataParser::getAllProcesses() const
{
    return _impl->allProcs;
}

std::size_t DataParser::getNConcurrentProcesses() const
{
    return _impl->maxProcs;
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

    QString line, absolutePath, fileName;
    QStringList tokens;
    bool ok1 = true, ok2 = true, ok3 = true;
    qint64 start, end;
    quint32 lineNumber = 0;


    while (!stream.atEnd()) {
        line = stream.readLine();
        tokens = line.split(" ");

        absolutePath = tokens.at(0);
        /// \todo delete msecs from command line app
        start = tokens.at(2).toLong(&ok2);
        end = tokens.at(3).toLong(&ok3);

        if (!ok1 || !ok2 || !ok3) {
            qWarning() << "Error parsing line" << lineNumber;
            return false;
        } else {
            _impl->processCompilationProcess(absolutePath, start, end);
        }

        lineNumber++;
    }
    _impl->concurrentProcs.clear();

    return true;
}

void DataParser::Pimpl::processCompilationProcess(const QString &path,
                                                  const qint64 start,
                                                  const qint64 end)
{
    if (!concurrentProcs.empty() && concurrentProcs.back().end < start) {
        concurrentProcs.pop_back();
    }

    concurrentProcs.emplace_back(path, start, end);
    allProcs.emplace_back(path, start, end);

    std::sort(concurrentProcs.begin(), concurrentProcs.end(), std::greater<CompilationProcess>());
    maxProcs = std::max(maxProcs, concurrentProcs.size());
}
