#pragma once

#include <QString>

enum class UnitType {
    SOURCE,
    LIBRARY,
    APP
};

struct CompileUnit {
    QString name;
    UnitType type;
};
