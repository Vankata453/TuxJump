//  SuperTux
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

#ifndef TUXJUMP_LEVEL_TILESET_HEADER
#define TUXJUMP_LEVEL_TILESET_HEADER

#include <string>
#include <map>

#include "level/tile.hpp"
#include "video/render_context.hpp"

// A class, which points tile IDs to their respective textures.
// Used to allow drawing a tile's texture on-screen.
class TileSet final
{
public:
  typedef std::pair<const int, Tile> TileEntry;
  typedef std::map<const int, Tile> TileEntries;

private:
  static const std::string s_tiles_folder;
  static const std::string s_tilesets_folder;

private:
  const std::string m_name;
  TileEntries m_tile_entries;

public:
  TileSet(const std::string& file);
  ~TileSet();

  void draw_tile(const RenderContext& context, const int& id,
                 const Positionf& pos, const bool& col_rect, const float& alpha) const;

  // Get tile data
  const TileEntry& get_tile_entry(const int& index) const;
  SDL_Texture* get_tile_texture(const int& index) const;

  // Get properties
  std::string get_tiles_folder() const;
  const TileEntries& get_tile_entries() const { return m_tile_entries; }

private:
  // Static utilities
  static std::string name_from_file(const std::string& file);

private:
  TileSet(const TileSet&) = delete;
  TileSet& operator=(const TileSet&) = delete;
};

#endif
