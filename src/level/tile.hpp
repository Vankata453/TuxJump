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

#ifndef TUXJUMP_LEVEL_TILE_HEADER
#define TUXJUMP_LEVEL_TILE_HEADER

#include "collision/object.hpp"

#include <string>

// Represents a tile in a level, with which can occur collision.
class Tile final : public CollisionObject
{
private:
  static const float s_width;

private:
  const int m_id;

public:
  Tile(const int& id, int x, int y);
  ~Tile();

  void apply_offset(const float& offset);

  // Get properties
  const int& get_id() const { return m_id; }

private:
  Tile(const Tile&) = delete;
  Tile& operator=(const Tile&) = delete;
};

#endif
