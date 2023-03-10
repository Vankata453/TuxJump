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

#include "gui/menu_item.hpp"

#include "game/resources.hpp"
#include "gui/menu_manager.hpp"

// Item to execute a callback.
MenuItem::MenuItem(const std::string& text, const MenuItem::Callback& callback) :
  m_text(text),
  m_callback(callback),
  m_id(-1)
{
}

// Item to invoke "menu_action()" on its menu.
MenuItem::MenuItem(const std::string& text, int id) :
  m_text(text),
  m_callback([this]() { MenuManager::current()->current_menu()->menu_action(*this); }),
  m_id(id)
{
}

MenuItem::~MenuItem()
{
}

void
MenuItem::draw(const RenderContext& context, const int& x, const int& y, bool selected)
{
  const auto text_rect = context.draw_text(Resources::Fonts::DEFAULT, m_text, x, y,
                                           ALIGN_CENTER, Resources::Colors::WHITE);
  if (selected) context.draw_line(text_rect.x, text_rect.y + text_rect.h, text_rect.x + text_rect.w, text_rect.y + text_rect.h,
                                  Resources::Colors::WHITE);
}

void
MenuItem::process_action(const ControlAction& action)
{
  switch (action)
  {
    case ACTION_CONFIRM:
    {
      m_callback();
      break;
    }
  }
}
