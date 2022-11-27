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

#include "level/tile.hpp"
#include "level/tileset.hpp"

class FileReader;

// A class to read and store level data.
// Also currently used for managing tiles.
class Level final : public CurrentObject<Level>
{
public:
  // Level data class
  class Data
  {
  public:
    int width;
    float spawn_height;

  public:
    Data();

    void read(FileReader& reader);
  };

private:
  Data m_data;

  std::unique_ptr<Tileset> m_tileset;
  std::vector<std::unique_ptr<Tile>> m_tiles;

public:
  Level(const std::string file_path);
  ~Level();

  void draw(RenderContext& context);

  void apply_offset(const float& offset);

  // Get properties
  const Data& get_data() const { return m_data; }
  const Tileset* get_tileset() const { return m_tileset.get(); }

private:
  void init_tiles(const std::vector<int> tiles);

private:
  Level(const Level&) = delete;
  Level& operator=(const Level&) = delete;
};

#endif
