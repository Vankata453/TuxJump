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

#ifndef TUXJUMP_UTIL_LOG_HEADER
#define TUXJUMP_UTIL_LOG_HEADER

#include <string>
#include <iostream>
#include <sstream>

#include "game/global.hpp"

namespace Log
{
  template<typename T>
  void warning(const T& data)
  {
    std::cout << GAME_TITLE << ": Warning: " << data << std::endl;
  }

  // Thrown errors will be caught in the GameManager.
  template<typename T>
  void fatal(const T& data)
  {
    throw std::runtime_error(GAME_TITLE + ": Fatal error: " + data);
  }
  template<typename T, typename U>
  void fatal(const T& lhs, const U& rhs)
  {
    std::stringstream err;
    err << GAME_TITLE << ": Fatal error: " << lhs << rhs << std::endl;
    throw std::runtime_error(err.str());
  }
};

#endif
