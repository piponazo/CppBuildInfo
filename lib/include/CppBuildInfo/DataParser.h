#pragma once

#include <QString>

class DataParser
{
public:
    /// Constructor.
    /// @param [in] path to file containing compilation times
    DataParser(const QString &path);

    /// Destructor.
    ~DataParser();

    /// Gets a list with the file names (without containing the directory)
    const QStringList & getFileNames() const;

    const QList<qint64> & getTimes() const;

    const QList<qint64> & getStartingTimes() const;

    const QList<qint64> & getEndingTimes() const;

    /// Gets the number of concurrent compilation processes
    int getNComcurrentProcesses() const;

private:
    bool parseData();

    struct Pimpl;
    Pimpl * _impl;
};
