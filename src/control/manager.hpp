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

#ifndef TUXJUMP_CONTROL_MANAGER_HEADER
#define TUXJUMP_CONTROL_MANAGER_HEADER

#include "util/current_object.hpp"

#include <vector>

#include "control/control.hpp"

class FileReader;
class FileWriter;

class ControlManager final : public CurrentObject<ControlManager>
{
  friend class ControlsMenu;

private:
  std::vector<Control> m_controls;

public:
  ControlManager();
  ~ControlManager();

  void load();

  void read(FileReader reader);
  void write(FileWriter writer);

  ControlAction get_action(const SDL_Keycode& key) const;

private:
  ControlManager(const ControlManager&) = delete;
  ControlManager& operator=(const ControlManager&) = delete;
};

#endif
