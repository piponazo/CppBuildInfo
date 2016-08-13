#pragma once

#include <QString>
#include <QHash>

class DataParser
{
public:
    /// Constructor.
    /// @param [in] path to file containing compilation times
    DataParser(const QString &path);

    /// Destructor.
    ~DataParser();

    /// Gets the data read from the file
    const QHash<QString, int> & getData() const;

private:
    bool parseData();

    struct Pimpl;
    Pimpl * _impl;
};
