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

#include "util/current_object.hpp"

#include <string>
#include <vector>
#include <memory>

#include "level/tilemap.hpp"
#include "level/tileset.hpp"
#include "video/color.hpp"

class FileReader;

// A class to store and manage the current level and its data.
class Level final : public CurrentObject<Level>
{
public:
  typedef std::vector<std::unique_ptr<TileMap>> TileMapList;

public:
  // Level data class
  class Data
  {
  public:
    int width;
    int height;
    float spawn_height;
    std::string background;
    Color background_fill;

  public:
    Data();

    void read(FileReader& reader);
  };

private:
  Data m_data;

  std::unique_ptr<TileSet> m_tileset;
  TileMapList m_tilemaps;

  SDL_Texture* m_background;

public:
  Level(const std::string& file_path);
  ~Level();

  void draw(const RenderContext& context, TileMap::Layer layer,
            const float& x_offset, const float& y_offset) const;
  void draw_background(const RenderContext& context) const;

  CollisionType collision(const Rectf& target, const float& x_offset,
                          const float& y_offset) const;

  // Get properties
  const Data& get_data() const { return m_data; }
  const TileMapList& get_tilemaps() const { return m_tilemaps; }
  const TileSet* get_tileset() const { return m_tileset.get(); }

private:
  Level(const Level&) = delete;
  Level& operator=(const Level&) = delete;
};

#endif
