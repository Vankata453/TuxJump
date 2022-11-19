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

// Create a specified menu
std::unique_ptr<Menu>
MenuFactory::create(MenuType type)
{
  auto menu = std::make_unique<Menu>();
  switch (type)
  {
    case MAIN_MENU:
    {
      menu->add_item("Start Game", []() { GameManager::instance().start_game(); });
      menu->add_item("Options", []() { MenuManager::instance().push_menu(OPTIONS_MENU); });
      menu->add_item("Quit", []() { GameManager::instance().quit_game(); });
      break;
    }
    case OPTIONS_MENU:
    {
      // TODO
      break;
    }
  }
  return std::move(menu);
}
