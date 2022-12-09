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

#include "util/file_reader.hpp"
#include "util/file_system.hpp"
#include "util/log.hpp"

const std::string Tileset::s_tiles_folder = "data/images/tiles";
const std::string Tileset::s_tilesets_folder = "data/images/tilesets";

Tileset::Tileset(const std::string& file) :
  m_name(name_from_file(file)),
  m_tile_files()
{
  FileReader reader(FileSystem::create_path(FileSystem::join(s_tilesets_folder, file)));

  for (auto& tile_entry : reader.get_entries())
    m_tile_files[std::stoi(tile_entry.first)] = tile_entry.second;
}

Tileset::~Tileset()
{
}

void
Tileset::draw_tile(RenderContext& context, const int& id, const Rectf& rect) const
{
  auto it = m_tile_files.find(id);
  if (it == m_tile_files.end())
    Log::fatal("No tile with ID " + std::to_string(id));

  context.draw_image(FileSystem::join(get_tiles_folder(), it->second), rect);
}

// Get properties

std::string
Tileset::get_tiles_folder() const
{
  return FileSystem::join(s_tiles_folder, m_name);
}

// Static utilities

std::string
Tileset::name_from_file(const std::string& file)
{
  size_t ext_pos = file.find_last_of('.');
  if (ext_pos == std::string::npos)
    return file;
  return file.substr(0, ext_pos);
}
