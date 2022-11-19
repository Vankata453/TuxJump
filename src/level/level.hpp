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

#ifndef TUXJUMP_LEVEL_LEVEL_HEADER
#define TUXJUMP_LEVEL_LEVEL_HEADER

#include <string>
#include <vector>

#include "level/tileset.hpp"
#include "video/render_context.hpp"

class Level final
{
private:
  static Level* s_current;

public:
  static Level& current();

private:
  static const int s_tile_width;

private:
  std::unique_ptr<Tileset> m_tileset;
  std::vector<int> m_tiles;
  int m_width;
  float m_spawn_height;

public:
  Level(const std::string file_path);
  ~Level();

  void draw(RenderContext& context);

  // Get properties
  const float& get_spawn_height() const { return m_spawn_height; }

private:
  Level(const Level&) = delete;
  Level& operator=(const Level&) = delete;
};

#endif
