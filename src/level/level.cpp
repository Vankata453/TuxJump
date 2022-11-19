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

#include "level/level.hpp"

#include <cassert>

#include "util/file_reader.hpp"
//#include "util/log.hpp"

// Allow easy access to the current level at all times
Level* Level::s_current = nullptr;

Level&
Level::current()
{
  assert(s_current);
  return *s_current;
}


const int Level::s_tile_width = 32;

Level::Level(const std::string file_path) :
  m_tileset(),
  m_tiles(),
  m_width(),
  m_spawn_height()
{
  s_current = this;

  FileReader reader("../" + file_path);

  m_tileset.reset(new Tileset(reader.get_string("tileset")));
  m_tiles = reader.read_int_array("tiles");
  reader.get("width", m_width, 5);
  reader.get("spawn_height", m_spawn_height, -1.0f);
}

Level::~Level()
{
  s_current = nullptr;
}

void
Level::draw(RenderContext& context)
{
  const std::string tiles_folder = m_tileset->get_tiles_folder();
  int row = 0;
  for (int i = 0; i < static_cast<int>(m_tiles.size()); i++)
  {
    const int& tile = m_tiles[i];
    if (tile <= 0) continue; // Empty tile

    row = (i == 0 ? 0 : i / m_width);
    context.draw_image(tiles_folder + "/" + m_tileset->get_tile_file(tile),
                        (i - row * m_width) * s_tile_width, row * s_tile_width,
                        s_tile_width, s_tile_width);
  }
}
