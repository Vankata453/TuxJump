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

#include "control/manager.hpp"

#include <algorithm>

#include "util/file_reader.hpp"
#include "util/file_writer.hpp"

ControlManager::ControlManager() :
  m_controls()
{
  load();
}

ControlManager::~ControlManager()
{
}

void
ControlManager::load()
{
  m_controls.clear();

  // Load defaults.
  m_controls.push_back({ ACTION_UP, "Up", SDLK_UP });
  m_controls.push_back({ ACTION_DOWN, "Down", SDLK_DOWN });
  m_controls.push_back({ ACTION_JUMP, "Jump", SDLK_SPACE });
  m_controls.push_back({ ACTION_CONFIRM, "Confirm", SDLK_RETURN });
}


void
ControlManager::read(FileReader reader)
{
  // Read custom control binds.
  for (Control& control : m_controls)
  {
    std::string key_name;
    if (reader.get(control.name, key_name))
      control.key = SDL_GetKeyFromName(key_name.c_str());
  }
}

void
ControlManager::write(FileWriter writer)
{
  for (const Control& control : m_controls)
  {
    writer.write(control.name, SDL_GetKeyName(control.key));
  }
}


ControlAction
ControlManager::get_action(const SDL_Keycode& key) const
{
  auto it = std::find_if(m_controls.begin(), m_controls.end(),
                         [key](const Control& control) { return control.key == key; });

  if (it == m_controls.end())
    return ACTION_NONE;

  return it->action;
}
