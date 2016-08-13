#include "DataParser.h"

#include <QFile>
#include <QTextStream>
#include <QHash>

#include <QDebug>

struct DataParser::Pimpl
{
    Pimpl (const QString &path)
        : file(path)
    {
    }

    QFile       file;

    QHash<QString, int> data;
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

const QHash<QString, int> &DataParser::getData() const
{
    return _impl->data;
}

bool DataParser::parseData()
{
    if (!_impl->file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error opening file";
        return false;
    }
    QTextStream stream (&_impl->file);

    QString line, sourceFile;
    QStringList tokens;
    bool ok = true;
    int msecs;
    quint32 lineNumber = 0;
    while (!stream.atEnd()) {
        line = stream.readLine();
        tokens = line.split(" ");
        sourceFile = tokens.at(0);
        msecs = tokens.at(1).toInt(&ok);
        if (ok == false) {
            qWarning() << "Error parsing line" << lineNumber;
        }

        _impl->data[sourceFile] = msecs;
        lineNumber++;
    }
    return true;
}
