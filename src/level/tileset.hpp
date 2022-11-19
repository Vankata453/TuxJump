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

class Tileset final
{
private:
  static const std::string s_tiles_folder;
  static const std::string s_tilesets_folder;

private:
  const std::string m_name;
  std::map<int, std::string> m_tile_files;

public:
  Tileset(const std::string& file);
  ~Tileset();

  std::string get_tiles_folder() const;
  std::string get_tile_file(const int id) const;

private:
  // Static utilities
  static std::string name_from_file(const std::string& file);
};

#endif
