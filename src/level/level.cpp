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

#include "util/file_reader.hpp"
#include "util/file_system.hpp"
#include "util/log.hpp"

Level::Data::Data() :
  width(5),
  spawn_height(-1.0f)
{
}

void
Level::Data::read(FileReader& reader)
{
  reader.get("width", width);
  reader.get("spawn_height", spawn_height);
}


Level::Level(const std::string file_path) :
  m_data(),
  m_tileset(),
  m_tiles()
{
  FileReader reader(FileSystem::create_path(file_path));

  m_data.read(reader);

  m_tileset.reset(new Tileset(reader.get_string("tileset")));
  init_tiles(reader.read_int_array("tiles"));
}

Level::~Level()
{
}

void
Level::init_tiles(const std::vector<int> tiles)
{
  int row = 0;
  for (int i = 0; i < static_cast<int>(tiles.size()); i++)
  {
    if (tiles[i] <= 0) continue; // Empty tile

    row = (i == 0 ? 0 : i / m_data.width);
    m_tiles.push_back(std::make_unique<Tile>(tiles[i], i - row * m_data.width, row));
  }
}

void
Level::draw(RenderContext& context)
{
  for (const auto& tile : m_tiles)
  {
    m_tileset->draw_tile(context, tile->get_id(), tile->get_rect());
    tile->draw(context); // Draw collision rect.
  }
}

void
Level::apply_offset(const float& offset)
{
  for (const auto& tile : m_tiles)
    tile->apply_offset(offset);
}
