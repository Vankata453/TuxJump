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

#ifndef TUXJUMP_LEVEL_TILEMAP_HEADER
#define TUXJUMP_LEVEL_TILEMAP_HEADER

#include <vector>

#include "collision/type.hpp"
#include "math/rect.hpp"

class RenderContext;
class TileSet;

// A class used to store and manage level tiles.
class TileMap final
{
public:
  enum Layer
  {
    LAYER_BACKGROUND,
    LAYER_INTERACTIVE,
    LAYER_FOREGROUND
  };

private:
  const int m_layer;
  const std::vector<int> m_tiles;

  const TileSet* m_tileset;

public:
  TileMap(int layer, std::vector<int> tiles, const TileSet* tileset);
  ~TileMap();

  void draw(RenderContext& context, const float& x_offset,
            const float& y_offset, const int& width) const;

  Positionf get_tile_pos(const int& index, const float& x_offset,
                         const float& y_offset, const int& width) const;
  CollisionType collision(const Rectf& target, const float& x_offset,
                          const float& y_offset, const int& width) const;

  Layer get_layer_type() const;

  // Get properties
  const int& get_layer() const { return m_layer; }

private:
  TileMap(const TileMap&) = delete;
  TileMap& operator=(const TileMap&) = delete;
};

#endif
