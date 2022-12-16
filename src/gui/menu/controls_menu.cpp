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

#include "gui/menu/controls_menu.hpp"

#include "control/manager.hpp"
#include "game/resources.hpp"

ControlsMenu::ControlsMenu() :
  m_modified_control()
{
  refresh();
}

void
ControlsMenu::refresh()
{
  clear();

  // Initialize all control items.
  for (Control& control : ControlManager::current()->m_controls)
  {
    add_item(control.name + ": " + SDL_GetKeyName(control.key), control.action);
  }
}

void
ControlsMenu::draw(RenderContext& context)
{
  if (m_modified_control)
  {
    // Draw "Press any key" prompt.
    context.draw_text(Resources::Fonts::DEFAULT, 
                      "Press any key to bind control for " + m_modified_control->name + "...",
                      context.get_width() / 2, context.get_height() / 2,
                      ALIGN_CENTER, Resources::Colors::WHITE);
  }
  else
  {
    // Draw the menu.
    Menu::draw(context);
  }
}

void
ControlsMenu::process_event(SDL_Event& ev)
{
  if (m_modified_control)
  {
    // Detect any key press and bind that key.
    if (ev.type == SDL_KEYDOWN)
    {
      m_modified_control->key = ev.key.keysym.sym;
      m_modified_control = nullptr;
      refresh();
    }
  }
  else
  {
    // Process menu events.
    Menu::process_event(ev);
  }
}

void
ControlsMenu::menu_action(MenuItem& item)
{
  // Set the control to be modified.
  for (Control& control : ControlManager::current()->m_controls)
  {
    if (control.action == item.get_id())
      m_modified_control = &control;
  }
}
