#pragma once

#include "CompileUnit.h"

/// @brief Interface for the compiler parsers, the ones extracting information from the compilation lines.
class ICompilerParser
{
public:
    virtual ~ICompilerParser() = default;

    virtual CompileUnit parse(const QString &compileLine, ProjectModel& model) const = 0;
};

