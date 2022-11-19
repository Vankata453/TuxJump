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

#include "video/render_context.hpp"
#include "gui/menu_item.hpp"

class Menu final
{
private:
  std::vector<std::unique_ptr<MenuItem>> m_items;
  int m_selected_item;

public:
  Menu();
  ~Menu();

  virtual void draw(RenderContext& context);
  virtual void process_event(SDL_Event& ev);

  // Importing items
  void add_item(const std::string name, const std::function<void ()>& callback = [](){});

  // Get dynamic properties (override to modify)
  virtual Position get_pos(Size context_size) { return { context_size.w / 2, context_size.h / 2 - context_size.h / 4 }; }

protected:
  // Menu actions
  void go_up();
  void go_down();

private:
  Menu(const Menu&) = delete;
  Menu& operator=(const Menu&) = delete;
};

#endif
