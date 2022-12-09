//  TuxJump
//  Copyright (C) 2022 Vankata453
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "util/file_system.hpp"

// Create a relative path to a file.
std::string
FileSystem::create_path(const std::string file)
{
  return "../" + file;
}

// Join two parts of a path together.
std::string
FileSystem::join(const std::string lhs, const std::string rhs)
{
  return lhs + "/" + rhs;
}
