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

#include "gui/menu_factory.hpp"

#include "game/manager.hpp"
#include "gui/menu_manager.hpp"
#include "gui/menu/controls_menu.hpp"
#include "gui/menu/options_menu.hpp"

// Create a specified menu
std::unique_ptr<Menu>
MenuFactory::create(MenuType type)
{
  Menu* menu;
  switch (type)
  {
    case MAIN_MENU:
    {
      menu = new Menu;
      menu->add_item("Start Game", []() { GameManager::current()->start_game(); });
      menu->add_item("Options", []() { MenuManager::current()->push_menu(OPTIONS_MENU); });
      menu->add_item("Quit", []() { GameManager::current()->quit_game(); });
      break;
    }
    case OPTIONS_MENU:
    {
      menu = new OptionsMenu;
      break;
    }
    case CONTROLS_MENU:
      menu = new ControlsMenu;
      break;
  }
  return std::unique_ptr<Menu>(menu);
}
