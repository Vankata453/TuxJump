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

#include "gui/menu.hpp"

#include "control/manager.hpp"

Menu::Menu() :
  m_items(),
  m_selected_item(0)
{
}

Menu::~Menu()
{
}

void
Menu::draw(const RenderContext& context)
{
  const Position menu_pos = get_pos();
  for (int i = 0; i < static_cast<int>(m_items.size()); i++)
  {
    m_items[i]->draw(context, menu_pos.x, menu_pos.y + 40 * (i + 1), i == m_selected_item);
  }
}

void
Menu::process_event(const SDL_Event& ev)
{
  if (m_items.empty()) return;

  if (ev.type != SDL_KEYDOWN) return;
  const ControlAction& action = ControlManager::current()->get_action(ev.key.keysym.sym);

  switch (action)
  {
    case ACTION_UP:
      go_up();
      break;
    case ACTION_DOWN:
      go_down();
      break;
    default:
      m_items[m_selected_item]->process_action(action); // If none of the menu navigation keys are pressed, process the event in the active item.
      break;
  }
}

// Menu actions

void
Menu::go_up()
{
  m_selected_item--;
  if (m_selected_item < 0) m_selected_item = static_cast<int>(m_items.size()) - 1;
}

void
Menu::go_down()
{
  m_selected_item++;
  if (m_selected_item >= static_cast<int>(m_items.size())) m_selected_item = 0;
}

// Menu utilities

void
Menu::clear()
{
  m_items.clear();
}
