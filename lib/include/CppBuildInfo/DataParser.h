#pragma once

#include <QString>

class CompilationProcess;

class DataParser
{
public:
    /// Constructor.
    /// @param [in] path to file containing compilation times
    DataParser(const QString &path);

    /// Destructor.
    ~DataParser();

    const std::vector<CompilationProcess> getAllProcesses() const;

    /// Gets the number of concurrent compilation processes
    std::size_t getNConcurrentProcesses() const;

    /// Gets the total time of the compilation [in msecs]
    std::size_t getTotalTime() const;

private:
    bool parseData();

    struct Pimpl;
    Pimpl * _impl;
};
