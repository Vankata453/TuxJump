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

#ifndef TUXJUMP_GUI_MENU_OPTIONS_MENU_HEADER
#define TUXJUMP_GUI_MENU_OPTIONS_MENU_HEADER

#include "gui/menu.hpp"

class OptionsMenu final : public Menu
{
public:
  OptionsMenu();

  void refresh() override;

private:
  void add_option(const std::string name, bool& var);

private:
  OptionsMenu(const OptionsMenu&) = delete;
  OptionsMenu& operator=(const OptionsMenu&) = delete;
};

#endif
