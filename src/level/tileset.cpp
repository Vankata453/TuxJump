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

#include "level/tileset.hpp"

#include "game/config.hpp"
#include "game/global.hpp"
#include "game/resources.hpp"
#include "math/rect.hpp"
#include "util/file_reader.hpp"
#include "util/file_system.hpp"
#include "util/log.hpp"

const std::string TileSet::s_tiles_folder = "images/tiles";
const std::string TileSet::s_tilesets_folder = "images/tilesets";

TileSet::TileSet(const std::string& file) :
  m_name(name_from_file(file)),
  m_tile_textures()
{
  FileReader reader(FileSystem::join(s_tilesets_folder, file));

  // Load each tile's texture.
  TextureManager* texture_manager = TextureManager::current();
  const std::string folder = get_tiles_folder();
  for (auto& tile_entry : reader.get_entries())
  {
    SDL_Texture* tile_texture = texture_manager->load_image(FileSystem::join(folder, tile_entry.second));
    m_tile_textures[std::stoi(tile_entry.first)] = tile_texture;
  }
}

TileSet::~TileSet()
{
}

void
TileSet::draw_tile(const RenderContext& context, const int& id,
                   const Positionf& pos) const
{
  auto it = m_tile_textures.find(id);
  if (it == m_tile_textures.end())
    Log::fatal("No tile with ID " + std::to_string(id));

  const Rectf rect(TILE_WIDTH * pos.x, TILE_WIDTH * pos.y, TILE_WIDTH, TILE_WIDTH);

  context.draw_texture(it->second, rect);
  if (CONFIG->show_col_rects) // Draw collision rect, if enabled.
    context.draw_rect(rect, Resources::Colors::RED);
}

// Get properties

std::string
TileSet::get_tiles_folder() const
{
  return FileSystem::join(s_tiles_folder, m_name);
}

// Static utilities

std::string
TileSet::name_from_file(const std::string& file)
{
  size_t ext_pos = file.find_last_of('.');
  if (ext_pos == std::string::npos)
    return file;
  return file.substr(0, ext_pos);
}
