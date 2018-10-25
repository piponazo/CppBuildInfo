#pragma once

#include <QString>

enum class UnitType {
    SOURCE_FILE,
    STATIC_LIBRARY,
    SHARED_LIBRARY,
    APPLICATION
};

struct CompileUnit {
    QString name;
    UnitType type;
};
