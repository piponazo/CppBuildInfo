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

#include "cbi_export.h"

#include "ICompilerParser.h"

#include <memory>

enum class CompilerType {
    GCC,
};

/// @brief Factory method for creating a ICompilerParser
CBI_EXPORT std::unique_ptr<ICompilerParser> createParser(const CompilerType compiler);
