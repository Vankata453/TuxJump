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

#include "game/config.hpp"

#include "control/manager.hpp"
#include "util/file_reader.hpp"
#include "util/file_writer.hpp"
#include "util/log.hpp"

GameConfig* CONFIG = nullptr; // Allow global access to the config.


const std::string GameConfig::s_target_file = "config.tjc";

GameConfig::GameConfig() :
  // Initialize config variables with default values.
  show_col_rects(false)
{
  CONFIG = this;

  read();
}

GameConfig::~GameConfig()
{
  save();

  CONFIG = nullptr;
}

void
GameConfig::read()
{
  try
  {
    FileReader reader(s_target_file);

    // Initialize managers/systems.
    ControlManager::current()->read(reader.for_subcategory("control"));

    // Initialize individual properties.
    reader.get("show_col_rects", show_col_rects);
  }
  catch (std::exception& err)
  {
    Log::warning("Error reading config file '" + s_target_file + "': " + err.what());
  }
}

void
GameConfig::save()
{
  FileWriter writer(s_target_file);

  // Write data for managers/systems.
  ControlManager::current()->write(writer.for_subcategory("control"));

  // Write data for individual properties.
  writer.write("show_col_rects", show_col_rects);
}
