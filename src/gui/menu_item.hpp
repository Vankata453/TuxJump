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

#include "control/control.hpp"
#include "video/render_context.hpp"

class MenuItem final
{
public:
  typedef std::function<void ()> Callback;

private:
  std::string m_text;
  Callback m_callback;
  const int m_id;

public:
  // Allow creation of two types of items: ones that use a callback, and others that invoke "menu_action()".
  MenuItem(const std::string& text, const Callback& callback);
  MenuItem(const std::string& text, int id);
  ~MenuItem();

  void draw(RenderContext& context, const int& x, const int& y, bool selected);
  void process_action(const ControlAction& action);

  // Get properties
  const int& get_id() const { return m_id; }

  // Set properties
  void set_text(const std::string text) { m_text = text; }
  void set_callback(const Callback& callback) { m_callback = callback; }

private:
  MenuItem(const MenuItem&) = delete;
  MenuItem& operator=(const MenuItem&) = delete;
};

#endif
