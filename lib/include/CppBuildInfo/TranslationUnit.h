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

#pragma once

#include <QString>

/// Compilation information about a single translation unit
struct TranslationUnit
{
public:
    TranslationUnit();
    TranslationUnit(const QString &_path, qint64 start, qint64 end);

    qint64 duration() const;
    QString fileName() const;

    bool operator < (const TranslationUnit &o) const;
    bool operator > (const TranslationUnit &o) const;

    QString absolutePath;   ///< File being compiled
    qint64  start;          ///< Time in which the compilation started
    qint64  end;            ///< Time in which the compilation ended
};
