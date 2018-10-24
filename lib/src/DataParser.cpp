#include <CppBuildInfo/DataParser.h>
#include <CppBuildInfo/TranslationUnit.h>

#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QStringList>

#include <QDebug>

#include <algorithm>

struct DataParser::Pimpl
{
    Pimpl (const QString &path)
        : file(path)
    {
    }

    bool parse();

    QFile file;
    std::vector<TranslationUnit> allProcs;
};

DataParser::DataParser() = default;

DataParser::~DataParser() = default;

const std::vector<TranslationUnit> DataParser::getAllProcesses() const
{
    return _impl->allProcs;
}

bool DataParser::parse(const QString &path)
{
    if (!QFile::exists(path))
    {
        qWarning() << "File does not exist:" << path;
        return false;
    }

    _impl = std::make_unique<Pimpl>(path);
    return _impl->parse();
}

bool DataParser::Pimpl::parse()
{
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error opening file: " << file.fileName();
        return false;
    }

    QTextStream stream (&file);
    QString line, absolutePath;
    QStringList tokens;
    bool okStart = true, okEnd = true;
    qint64 start, end;
    quint32 lineNumber = 0;


    while (!stream.atEnd()) {
        line = stream.readLine();
        tokens = line.split(QRegExp("\\s+"));

        if (tokens.size() != 3) {
            qWarning() << "Error parsing line" << lineNumber << "incorrect number of tokens";
            return false;
        }

        absolutePath = tokens.at(0);
        start = tokens.at(1).toLongLong(&okStart);
        end = tokens.at(2).toLongLong(&okEnd);

        if (!okStart || !okEnd) {
            qWarning() << "Error parsing line" << lineNumber;
            return false;
        } else {
            allProcs.emplace_back(absolutePath, start, end);
        }

        lineNumber++;
    }

    /// \note Not sure if this should be done here or outside of the class.
    std::sort(allProcs.begin(), allProcs.end(),
        [](const TranslationUnit & a, const TranslationUnit & b) -> bool
        {
            return a.start < b.start;
        });

    return true;
}
