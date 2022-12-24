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

#include "game/global.hpp"
#include "level/level.hpp"

Editor::Editor() :
  m_level(new Level("levels/test.tjl")),
  m_pos(0.f, 0.f),
  m_selected_tilemap(0)
{
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
}

void
Editor::draw(const RenderContext& context)
{
  m_level->draw_background(context);

  const Level::TileMapList& tilemaps = m_level->get_tilemaps();
  for (int i = 0; i < static_cast<int>(tilemaps.size()); i++)
  {
    // Draw all tilemaps. The selected one should have the highest alpha value.
    tilemaps[i]->draw(context, m_pos.x, m_pos.y, false, (i == m_selected_tilemap ? 255 : 125));
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
        case SDLK_LEFT:
          if (m_pos.x > 0.f) m_pos.x -= 0.1f;
          break;
        case SDLK_RIGHT:
          if (m_pos.x < m_level->get_data().width * TILE_WIDTH) m_pos.x += 0.1f;
          break;
        case SDLK_v:
          if (m_selected_tilemap > 0) m_selected_tilemap--;
          break;
        case SDLK_b:
          if (m_selected_tilemap < static_cast<int>(m_level->get_tilemaps().size()) - 1) m_selected_tilemap++;
          break;
      }
    }
  }
}
