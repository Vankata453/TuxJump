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

class Level;
class RenderContext;

// A class used to store and manage level tiles.
class TileMap final
{
public:
  typedef std::vector<int> Tiles;

public:
  enum Layer
  {
    LAYER_BACKGROUND,
    LAYER_INTERACTIVE,
    LAYER_FOREGROUND
  };

private:
  const int m_layer;
  Tiles m_tiles;
  const Level* m_parent;

public:
  TileMap(int layer, std::vector<int> tiles, const Level* parent);
  ~TileMap();

  void draw(const RenderContext& context, const float& x_offset,
            const float& y_offset, const bool& col_rects = true, const float& alpha = 255) const;

  Positionf get_tile_pos(const int& index, const float& x_offset,
                         const float& y_offset, const int& width) const;
  CollisionType collision(const Rectf& target, const float& x_offset,
                          const float& y_offset) const;

  void insert_tile(const int& id, const Position& coords);
  void resize(const int& add_width, const int& add_height);

  Layer get_layer_type() const;

  // Get properties
  const int& get_layer() const { return m_layer; }

private:
  TileMap(const TileMap&) = delete;
  TileMap& operator=(const TileMap&) = delete;
};

#endif
