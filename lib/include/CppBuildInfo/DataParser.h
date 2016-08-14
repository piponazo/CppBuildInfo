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

    const QList<int> & getTimes() const;

    const QList<int> & getStartingTimes() const;

    const QList<int> & getEndingTimes() const;

    /// Gets the number of concurrent compilation processes
    int getNComcurrentProcesses() const;

private:
    bool parseData();

    struct Pimpl;
    Pimpl * _impl;
};
