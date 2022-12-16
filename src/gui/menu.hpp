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

#ifndef TUXJUMP_GUI_MENU_HEADER
#define TUXJUMP_GUI_MENU_HEADER

#include <SDL2/SDL.h>

#include <memory>
#include <functional>
#include <vector>

#include "control/control.hpp"
#include "gui/menu_item.hpp"
#include "video/render_context.hpp"

class Menu
{
private:
  std::vector<std::unique_ptr<MenuItem>> m_items;
  int m_selected_item;

public:
  Menu();
  ~Menu();

  virtual void refresh() {}

  virtual void draw(RenderContext& context);
  virtual void process_event(SDL_Event& ev);

  virtual void menu_action(MenuItem& item) {}

  // Importing items
  template<typename... Args>
  void add_item(Args&&... args)
  {
    m_items.push_back(std::make_unique<MenuItem>(std::forward<Args>(args)...));
  }

  // Get dynamic properties (override to modify)
  virtual Position get_pos(Size context_size) { return { context_size.w / 2, context_size.h / 2 - context_size.h / 4 }; }

protected:
  // Menu actions
  void go_up();
  void go_down();

  // Menu utilities
  void clear();

private:
  Menu(const Menu&) = delete;
  Menu& operator=(const Menu&) = delete;
};

#endif
