/* Cpp Build Info
   Copyright (C) 2016 Luis Díaz Más

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#include "GccCompilerParser.h"

#include <CppBuildInfo/CompilerParserFactory.h>

#include <QDebug>
#include <QRegExp>
#include <QStringList>

namespace
{
    void assertGccTools(const QString& firstCommand)
    {
        if (!firstCommand.endsWith("c++") && !firstCommand.endsWith("ar") && !firstCommand.endsWith("ranlib")) {
            throw std::runtime_error("no tools related with gcc found");
        }
    }

    void addStaticLibObjects(const QString& libName, const QStringList& list, ProjectModel& model)
    {
        std::vector<size_t> indexesToSources;
        for (auto it = list.begin() + 3; it != list.end(); ++it) {
            for (size_t i = 0; i < model.units.size(); i++) {
                if (model.units[i].objectFile == *it) {
                    indexesToSources.push_back(i);
                }
            }
        }
        model.relations[libName.toStdString()] = indexesToSources;
    }

}  // namespace

CompileUnit GccCompilerParser::parse(const QString& compileLine, ProjectModel &model) const
{
    QStringList list = compileLine.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    assertGccTools(list.first());

    CompileUnit ret;

    if (list.indexOf("-rdynamic") != -1) {
        const int indexApp = list.indexOf("-o");
        ret.name = list.at(indexApp + 1).split("/").last();
        ret.type = UnitType::APPLICATION;
    } else {
        const int indexC = list.indexOf("-c");
        const int indexShared = list.indexOf("-shared");
        const int indexStatic = list.indexOf("qc");
        if (indexShared != -1) {
            ret.name = list.at(indexShared + 1).split(",").last();
            ret.type = UnitType::SHARED_LIBRARY;
        } else if (indexC != -1) {
            ret.name = list.at(indexC + 1);
            ret.type = UnitType::SOURCE_FILE;
        } else if (indexStatic != -1){
            // In gcc we have something like: /usr/bin/ar qc path/to/lib.a
            ret.name = list.at(indexStatic + 1).split("/").last();
            ret.type = UnitType::STATIC_LIBRARY;
            addStaticLibObjects(ret.name, list, model);
        } else {
            ret.type = UnitType::UNKNOWN;
            return ret;
        }
    }

    model.units.push_back(ret);

    return ret;
}
