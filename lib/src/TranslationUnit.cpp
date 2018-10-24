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

#include <CppBuildInfo/TranslationUnit.h>

TranslationUnit::TranslationUnit()
  : start(0)
  , end(0)
{
}

TranslationUnit::TranslationUnit(const QString &_path, qint64 _start, qint64 _end)
  : absolutePath(_path)
  , start(_start)
  , end(_end)
{
}

qint64 TranslationUnit::duration() const
{
    return end - start;
}

QString TranslationUnit::fileName() const
{
    const int idxLastSlash = absolutePath.lastIndexOf('/');
    return absolutePath.mid(idxLastSlash + 1);
}

bool TranslationUnit::operator <(const TranslationUnit &o) const
{
    return end < o.end;
}

bool TranslationUnit::operator >(const TranslationUnit &o) const
{
    return end >= o.end;
}
