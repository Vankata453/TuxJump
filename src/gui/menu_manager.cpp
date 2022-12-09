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

#include "gui/menu_manager.hpp"

#include "game/manager.hpp"

MenuManager::MenuManager() :
  m_menu_stack()
{
  push_menu(MenuType::MAIN_MENU); // Show the main menu by default.
}

MenuManager::~MenuManager()
{
}

void
MenuManager::draw(RenderContext& context)
{
  if (!is_active()) return;

  current_menu()->draw(context);
}

void
MenuManager::process_event(SDL_Event& ev)
{
  if (!is_active()) return;

  switch (ev.type)
  {
    case SDL_KEYDOWN:
    {
      switch (ev.key.keysym.sym)
      {
        case SDLK_ESCAPE:
          pop_menu();
          break;
        default:
          current_menu()->process_event(ev); // If none of the keys for navigation through menus is pressed, process the event in the current menu.
          break;
      }
    }
  }
}

// Menu management

void
MenuManager::push_menu(std::unique_ptr<Menu> menu)
{
  m_menu_stack.push_back(std::move(menu));
}

void
MenuManager::push_menu(MenuType type)
{
  push_menu(MenuFactory::create(type));
}

void
MenuManager::pop_menu()
{
  if (m_menu_stack.size() <= 1) return;

  m_menu_stack.pop_back();
}

void
MenuManager::clear_menu_stack()
{
  m_menu_stack.clear();
}
