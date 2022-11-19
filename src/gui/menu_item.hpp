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

#ifndef TUXJUMP_GUI_MENU_ITEM_HEADER
#define TUXJUMP_GUI_MENU_ITEM_HEADER

#include <SDL2/SDL.h>

#include <memory>
#include <functional>
#include <string>

#include "video/render_context.hpp"

class MenuItem final
{
private:
  std::string m_text;
  std::function<void ()> m_callback;

public:
  MenuItem(const std::string text, const std::function<void ()>& callback = [](){});
  ~MenuItem();

  void draw(RenderContext& context, int x, int y, bool selected);
  void process_event(SDL_Event& ev);

  // Set properties
  void set_text(const std::string text) { m_text = text; }
  void set_callback(const std::function<void ()>& callback) { m_callback = callback; }

private:
  MenuItem(const MenuItem&) = delete;
  MenuItem& operator=(const MenuItem&) = delete;
};

#endif
