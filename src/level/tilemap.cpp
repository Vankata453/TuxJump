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

#include "level/tilemap.hpp"

#include "collision/util.hpp"
#include "game/global.hpp"
#include "level/level.hpp"
#include "level/tileset.hpp"
#include "util/log.hpp"

TileMap::TileMap(int layer, std::vector<int> tiles, const Level* parent) :
  m_layer(layer),
  m_tiles(std::move(tiles)),
  m_parent(parent)
{
  const Level::Data& level_data = m_parent->get_data();
  const float tiles_total = level_data.width * level_data.height;
  // If tiles are less than the level width, add zeros to fill the remaining space.
  while (static_cast<int>(m_tiles.size()) < tiles_total)
  {
    m_tiles.push_back(0);
  }
  // If tiles are more than the level width, remove tiles from the end.
  while (static_cast<int>(m_tiles.size()) > tiles_total)
  {
    m_tiles.pop_back();
  }
}

TileMap::~TileMap()
{
}


void
TileMap::draw(const RenderContext& context, const float& x_offset,
              const float& y_offset, const bool& col_rects, const float& alpha) const
{
  const TileSet* tileset = m_parent->get_tileset();
  const int& width = m_parent->get_data().width;

  for (int i = 0; i < static_cast<int>(m_tiles.size()); i++)
  {
    if (m_tiles[i] <= 0) continue; // Empty tile

    tileset->draw_tile(context, m_tiles[i], get_tile_pos(i, x_offset, y_offset, width),
                       col_rects, alpha);
  }
}


Positionf
TileMap::get_tile_pos(const int& index, const float& x_offset,
                      const float& y_offset, const int& width) const
{
  const int row = (index == 0 ? 0 : index / width);
  return { index - row * width - x_offset, row - y_offset };
}

CollisionType
TileMap::collision(const Rectf& target, const float& x_offset,
                   const float& y_offset) const
{
  const int width = m_parent->get_data().width;

  for (int i = 0; i < static_cast<int>(m_tiles.size()); i++)
  {
    if (m_tiles[i] <= 0) continue; // Empty tile

    const Positionf tile_pos = get_tile_pos(i, x_offset, y_offset, width);
    const Rectf tile_rect(TILE_WIDTH * tile_pos.x, TILE_WIDTH * tile_pos.y, TILE_WIDTH, TILE_WIDTH);

    const CollisionType col = CollisionUtil::collision(tile_rect, target);
    if (col != COLLISION_NONE)
      return col;
  }

  return COLLISION_NONE;
}


void
TileMap::insert_tile(const int& id, const Position& coords)
{
  const int index = m_parent->get_data().width * coords.y + coords.x;
  if (index < 0 || index >= static_cast<int>(m_tiles.size())) return; // Make sure the index is valid.
  m_tiles[index] = id;
}

void
TileMap::resize(const int& add_width, const int& add_height)
{
  // Modify a local copy of the tiles, in case of an error.
  TileMap::Tiles tiles = m_tiles;

  int width = m_parent->get_data().width;
  const int& height = m_parent->get_data().height;

  if (add_width < 0) // Removing width.
  {
    const int remove_width = add_width * -1;

    if (remove_width >= width) // Check for invalid "remove_width" value.
      throw std::runtime_error("Cannot remove width, which is equal to or more than the current width.");

    for (int i = width - remove_width - 1; i < static_cast<int>(tiles.size()); i += width - remove_width)
    {
      // Remove the last tile "add_width" times for every row.
      for (int y = 0; y < remove_width; y++)
        tiles.erase(tiles.begin() + i + 1);
    }
    width -= remove_width;
  }
  else // Adding width.
  {
    for (int i = width; i < static_cast<int>(tiles.size()) + add_width; i += width + add_width)
    {
      // Insert an empty tile "add_width" times on every row.
      for (int y = 0; y < add_width; y++)
        tiles.insert(tiles.begin() + i, 1);
    }
    width += add_width;
  }

  if (add_height < 0) // Removing height.
  {
    const int remove_height = add_height * -1;

    if (remove_height >= height) // Check for invalid "remove_height" value.
      throw std::runtime_error("Cannot remove height, which is equal to or more than the current height.");

    // Remove the last row every "add_height" times.
    for (int y = 0; y < remove_height * width; y++)
      tiles.pop_back();
  }
  else // Adding height.
  {
    // Insert a new row every "add_height" times.
    for (int y = 0; y < add_height * width; y++)
      tiles.push_back(1);
  }

  // No errors have occured, so apply the local tile changes.
  m_tiles = tiles;
}


TileMap::Layer
TileMap::get_layer_type() const
{
  if (m_layer < 0)
    return LAYER_BACKGROUND;
  else if (m_layer >= 100)
    return LAYER_FOREGROUND;

  return LAYER_INTERACTIVE;
}
