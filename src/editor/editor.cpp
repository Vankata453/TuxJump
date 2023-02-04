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

#include "editor/editor.hpp"

#include "editor/overlay.hpp"
#include "editor/toolbox.hpp"
#include "game/global.hpp"
#include "level/level.hpp"

const float Editor::s_nav_speed = 0.1f;

Editor::Editor() :
  m_level(new Level("levels/test.tjl")),
  m_widgets(),
  m_reverse_widgets(),
  m_pos(0.f, 0.f),
  m_selected_tilemap(0),
  m_control_held(false)
{
  // Initialize widgets from back to front.
  #define EDITOR_INIT_WIDGET(Class) m_widgets.push_back(std::unique_ptr<EditorWidget>(new Class()));
  EDITOR_INIT_WIDGET(EditorOverlay);
  EDITOR_INIT_WIDGET(EditorToolbox);

  // Reverse all widgets for use, when processing events,
  // since events should be processed from the frontmost widget, backwards.
  for (int i = static_cast<int>(m_widgets.size()) - 1; i >= 0; i--)
  {
    m_reverse_widgets.push_back(m_widgets[i].get());
  }

  // Select the first interactive tilemap, if any.
  const Level::TileMapList& tilemaps = m_level->get_tilemaps();
  for (int i = 0; i < static_cast<int>(tilemaps.size()); i++)
  {
    if (tilemaps[i]->get_layer_type() == TileMap::LAYER_INTERACTIVE)
    {
      m_selected_tilemap = i;
      break;
    }
  }
}

Editor::~Editor()
{
  // Reset the tile width to its default.
  TILE_WIDTH = TILE_WIDTH_DEFAULT;
}

void
Editor::draw(const RenderContext& context)
{
  m_level->draw_background(context);

  const Level::TileMapList& tilemaps = m_level->get_tilemaps();
  for (int i = 0; i < static_cast<int>(tilemaps.size()); i++)
  {
    // Draw all tilemaps, other than the selected one.
    if (i == m_selected_tilemap) continue;
    tilemaps[i]->draw(context, m_pos.x, m_pos.y, false, 125);
  }
  // Draw the selected tilemap last.
  tilemaps[m_selected_tilemap]->draw(context, m_pos.x, m_pos.y, false);

  // Update and draw widgets.
  for (auto& widget : m_widgets)
  {
    widget->update();
    widget->draw(context);
  }
}

void
Editor::process_event(const SDL_Event& ev)
{
  switch (ev.type)
  {
    case SDL_KEYDOWN:
    {
      switch (ev.key.keysym.sym)
      {
        case SDLK_LCTRL:
        case SDLK_RCTRL:
          m_control_held = true; // Indicate a CTRL key is being held.
          break;
        case SDLK_LEFT:
          // Navigate left in level.
          if (m_pos.x > 0.f)
            m_pos.x -= s_nav_speed;
          break;
        case SDLK_RIGHT:
          // Navigate right in level.
          if (m_pos.x + SCREEN_WIDTH / TILE_WIDTH < m_level->get_data().width)
            m_pos.x += s_nav_speed;
          break;
        case SDLK_UP:
          // Navigate up in level.
          if (m_pos.y > 0.f)
            m_pos.y -= s_nav_speed;
          break;
        case SDLK_DOWN:
          // Navigate down in level.
          if (m_pos.y + SCREEN_HEIGHT / TILE_WIDTH < m_level->get_data().height)
            m_pos.y += s_nav_speed;
          break;
        case SDLK_v:
          // Switch to previous tilemap.
          if (m_selected_tilemap > 0)
            m_selected_tilemap--;
          break;
        case SDLK_b:
          // Switch to next tilemap.
          if (m_selected_tilemap < static_cast<int>(m_level->get_tilemaps().size()) - 1)
            m_selected_tilemap++;
          break;
      }
      break;
    }
    case SDL_KEYUP:
    {
      switch (ev.key.keysym.sym)
      {
        case SDLK_LCTRL:
        case SDLK_RCTRL:
          m_control_held = false; // Indicate a CTRL key isn't being held anymore.
          break;
      }
      break;
    }
    case SDL_MOUSEWHEEL:
    {
      // Zoom in/out, using the mouse wheel, when holding CTRL.
      if (m_control_held)
        TILE_WIDTH += ev.wheel.preciseY;
      break;
    }
    case SDL_MOUSEMOTION:
    {
      for (auto& widget : m_reverse_widgets)
        if (widget->process_mouse_motion(ev.motion)) break;
      break;
    }
    case SDL_MOUSEBUTTONDOWN:
    {
      for (auto& widget : m_reverse_widgets)
        if (widget->process_mouse_down(ev.button)) break;
      break;
    }
    case SDL_MOUSEBUTTONUP:
    {
      for (auto& widget : m_reverse_widgets)
        if (widget->process_mouse_up(ev.button)) break;
      break;
    }
  }

  check_level_pos();
}


void
Editor::check_level_pos()
{
  // If the position is below 0, make it exactly 0.
  if (m_pos.x < 0.0f) m_pos.x = 0.0f;
  if (m_pos.y < 0.0f) m_pos.y = 0.0f;
}

// Get properties

TileMap&
Editor::get_selected_tilemap() const
{
  return *m_level->get_tilemaps().at(m_selected_tilemap);
}
