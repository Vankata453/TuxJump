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

#include <algorithm>

#include "util/file_reader.hpp"
#include "util/file_system.hpp"

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
  m_tilemaps()
{
  FileReader reader(FileSystem::create_path(file_path));

  // Read level data.
  m_data.read(reader);

  // Initialize the current tileset.
  TileSet* tileset = new TileSet(reader.get_string("tileset"));
  m_tileset.reset(tileset);

  // Iterate through all tilemaps and load them.
  FileReader tilemap_reader = reader.for_subcategory("tilemap");
  std::vector<int> current_tiles;
  for (int i = 0; i < 500; i++) // Allow for a maximum of 500 tilemaps.
  {
    try
    {
      FileReader tilemap_data_reader = tilemap_reader.for_subcategory(std::to_string(i));

      // Get tilemap data.
      int layer = 0;
      tilemap_data_reader.get("layer", layer);

      m_tilemaps.push_back(std::make_unique<TileMap>(layer, tilemap_data_reader.read_int_array("tiles"), tileset));
    }
    catch (...) // There are no more tilemaps available.
    {
      break;
    }
  }

  // Sort tilemaps in ascending order by layer index.
  std::sort(m_tilemaps.begin(), m_tilemaps.end(),
    [](const auto& lhs, const auto& rhs) {
      return lhs->get_layer() < rhs->get_layer();
    });
}

Level::~Level()
{
}


void
Level::draw(RenderContext& context, TileMap::Layer layer,
            const float& x_offset, const float& y_offset) const
{
  // Draw a specified tilemap layer type.
  for (const auto& tilemap : m_tilemaps)
  {
    if (tilemap->get_layer_type() == layer)
      tilemap->draw(context, x_offset, y_offset, m_data.width);
  }
}

CollisionType
Level::collision(const Rectf& target, const float& x_offset,
                 const float& y_offset) const
{
  // Check for collision in interactive tilemaps.
  for (const auto& tilemap : m_tilemaps)
  {
    if (tilemap->get_layer_type() != TileMap::LAYER_INTERACTIVE) continue;

    const CollisionType col = tilemap->collision(target, x_offset, y_offset, m_data.width);
    if (col != COLLISION_NONE)
      return col;
  }

  return COLLISION_NONE;
}
