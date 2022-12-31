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

#ifndef TUXJUMP_GUI_MENU_MANAGER_HEADER
#define TUXJUMP_GUI_MENU_MANAGER_HEADER

#include "game/mode.hpp"

#include <memory>
#include <vector>

#include "gui/menu_factory.hpp"

class MenuManager final : public CurrentObject<MenuManager>
{
private:
  std::vector<std::unique_ptr<Menu>> m_menu_stack;

public:
  MenuManager();
  ~MenuManager() override;

  void draw(const RenderContext& context);
  bool process_event(const SDL_Event& ev);

  // Menu management
  void push_menu(std::unique_ptr<Menu> menu);
  void push_menu(MenuType type);
  void pop_menu();
  void clear_menu_stack();

  // Get dynamic properties
  bool is_active() { return !m_menu_stack.empty(); }
  Menu* current_menu() { return m_menu_stack.end()[-1].get(); }

private:
  MenuManager(const MenuManager&) = delete;
  MenuManager& operator=(const MenuManager&) = delete;
};

#endif

