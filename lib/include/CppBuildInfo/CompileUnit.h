#pragma once

#include <QString>

#include <vector>
#include <unordered_map>

enum class UnitType {
    UNKNOWN = -1,
    SOURCE_FILE,
    STATIC_LIBRARY,
    SHARED_LIBRARY,
    APPLICATION
};

struct CompileUnit {
    QString name;
    QString objectFile;  ///< Only set when it is a SOURCE_FILE
    UnitType type;

    CompileUnit() = default;

    CompileUnit(const QString&& name_, const QString&& objectFile_, UnitType type_):
        name(std::move(name_))
      , objectFile(std::move(objectFile_))
      , type(type_)
    {
    }
};

struct ProjectModel {
    std::vector<CompileUnit> units;
    std::unordered_map<std::string, std::vector<size_t>> relations;
};
