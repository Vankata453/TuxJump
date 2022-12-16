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

GameConfig::GameConfig()
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

    ControlManager::current()->read(reader);
  }
  catch (...) // In a case when there isn't a config file.
  {
    Log::warning("No '" + s_target_file + "' config file found.");
  }
}

void
GameConfig::save()
{
  FileWriter writer(s_target_file);

  ControlManager::current()->write(writer);
}
