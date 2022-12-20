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

#ifndef TUXJUMP_VIDEO_COLOR_HEADER
#define TUXJUMP_VIDEO_COLOR_HEADER

#include <SDL2/SDL.h>

#include <string>
#include <vector>

#include "util/log.hpp"

class Color final
{
public:
  int r, g, b, a;

public:
  static Color from_array(const std::vector<int>& arr)
  {
    if (arr.size() < 3)
    {
      Log::fatal("Cannot create color from an array with less than 3 values.");
    }
    return { arr[0], arr[1], arr[2], (arr.size() > 3 ? arr[3] : 255) };
  }

public:
  Color(const int& r_, const int& g_, const int& b_, int a_ = 255) :
    r(r_),
    g(g_),
    b(b_),
    a(a_)
  {}

  std::string to_string() const
  {
    return std::to_string(r) + " " + std::to_string(g) + " " +
           std::to_string(b) + " " + std::to_string(a);
  }
  SDL_Color to_sdl() const
  {
    return { static_cast<uint8_t>(r), static_cast<uint8_t>(g),
             static_cast<uint8_t>(b), static_cast<uint8_t>(a) };
  }
};

#endif
