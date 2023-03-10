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

class Log
{
public:
  static void warning(const std::string& text)
  {
    std::cout << GAME_TITLE << ": Warning: " << text << std::endl;
  }

  // Thrown errors will be caught in the GameManager.
  template<typename T>
  static void fatal(T text)
  {
    throw std::runtime_error(GAME_TITLE + ": Fatal error: " + text);
  }

  template<typename T, typename U>
  static void fatal(T text, U data)
  {
    std::stringstream err;
    err << GAME_TITLE << ": Fatal error: " << text << data << std::endl;
    throw std::runtime_error(err.str());
  }
};

#endif
