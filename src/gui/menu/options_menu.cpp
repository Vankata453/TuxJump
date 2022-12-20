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

#include "gui/menu/options_menu.hpp"

#include "game/config.hpp"
#include "gui/menu_manager.hpp"

OptionsMenu::OptionsMenu()
{
  refresh();
}

void
OptionsMenu::refresh()
{
  clear();

  // Add options.
  add_option("Show Collision Rects", CONFIG->show_col_rects);

  // List additional menus.
  add_item("Keyboard Controls",
    []() {
      MenuManager::current()->push_menu(CONTROLS_MENU);
    });
}


void
OptionsMenu::add_option(const std::string& name, bool& var)
{
  add_item(name + ": " + (var ? "ON" : "OFF"),
    [this, &var]() {
      var = !var;
      refresh();
    });
}
