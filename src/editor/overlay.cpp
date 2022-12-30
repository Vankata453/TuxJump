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

#include "editor/overlay.hpp"

#include "editor/editor.hpp"
#include "game/global.hpp"
#include "game/resources.hpp"
#include "level/level.hpp"

EditorOverlay::EditorOverlay() :
  m_width(Level::current()->get_data().width),
  m_height(Level::current()->get_data().height),
  m_pos(Editor::current()->get_pos()),
  m_inserting_tiles(false),
  m_selected_tile(),
  m_preview_coords(-1, -1)
{
}

EditorOverlay::~EditorOverlay()
{
}


void
EditorOverlay::draw(const RenderContext& context)
{
  // Pre-calculate if width and/or height are limited (not to fit on the full screen).
  const float width = m_width < context.get_width() / TILE_WIDTH ? m_width * TILE_WIDTH : context.get_width();
  const float height = m_height < context.get_height() / TILE_WIDTH ? m_height * TILE_WIDTH : context.get_height();

  // Draw vertical grid lines.
  float drawn_x = TILE_WIDTH - m_pos.x * TILE_WIDTH;
  for (int i = 0; i < m_width && drawn_x <= context.get_width(); i++)
  {
    context.draw_line(drawn_x, 0, drawn_x, height,
                      Resources::Colors::WHITE);
    drawn_x += TILE_WIDTH;
  }
  // Draw horizontal grid lines.
  float drawn_y = TILE_WIDTH - m_pos.y * TILE_WIDTH;
  for (int i = 0; i < m_height && drawn_y <= context.get_height(); i++)
  {
    context.draw_line(0, drawn_y, width, drawn_y,
                      Resources::Colors::WHITE);
    drawn_y += TILE_WIDTH;
  }

  // Draw a preview of the selected tile, if such is available and it is within the grid range.
  if (m_selected_tile && m_preview_coords.x > -1 && m_preview_coords.y > -1 &&
                         m_preview_coords.x < m_width && m_preview_coords.y < m_height)
  {
    context.draw_texture(m_selected_tile->second.texture,
                         m_preview_coords.x * TILE_WIDTH, m_preview_coords.y * TILE_WIDTH,
                         TILE_WIDTH, TILE_WIDTH, 85);
  }
}

void
EditorOverlay::update()
{
  insert_tile(); // Update the insertion of tiles, in case the mouse is held.
}


bool
EditorOverlay::process_mouse_motion(const SDL_MouseMotionEvent& motion)
{
  if (!m_selected_tile) return false; // No selected tile.

  // Find X tile preview position.
  int tile_check_x = 0;
  while (tile_check_x < SCREEN_WIDTH)
  {
    if (motion.x >= tile_check_x &&
        motion.x <= tile_check_x + TILE_WIDTH) break;
    tile_check_x += TILE_WIDTH;
  }
  // Find Y tile preview position.
  int tile_check_y = 0;
  while (tile_check_y < SCREEN_HEIGHT)
  {
    if (motion.y >= tile_check_y &&
        motion.y <= tile_check_y + TILE_WIDTH) break;
    tile_check_y += TILE_WIDTH;
  }

  // Set the tile preview coordinates.
  m_preview_coords = { static_cast<int>(tile_check_x / TILE_WIDTH),
                       static_cast<int>(tile_check_y / TILE_WIDTH) };
  return true;
}

bool
EditorOverlay::process_mouse_down(const SDL_MouseButtonEvent& button)
{
  m_inserting_tiles = true; // Start inserting tiles.
  return true;
}

bool
EditorOverlay::process_mouse_up(const SDL_MouseButtonEvent& button)
{
  m_inserting_tiles = false; // Stop inserting tiles.
  return true;
}


void
EditorOverlay::insert_tile()
{
  if (!m_inserting_tiles || !m_selected_tile ||
      m_preview_coords.x < 0 || m_preview_coords.y < 0 ||
      m_preview_coords.x >= m_width || m_preview_coords.y >= m_height)
    return; // Tiles are not being inserted, no selected tile, or no valid preview position.

  // Insert a tile at the current preview position on the selected tilemap.
  Editor::current()->get_selected_tilemap().insert_tile(m_selected_tile->first, m_preview_coords);
}
