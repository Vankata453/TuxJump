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

#include "editor/toolbox.hpp"

#include "editor/editor.hpp"
#include "editor/overlay.hpp"
#include "game/resources.hpp"
#include "level/level.hpp"
#include "level/tileset.hpp"

const float EditorToolbox::s_height = 80.f;
const float EditorToolbox::s_collapse_bar_height = 15.f;
const float EditorToolbox::s_hover_resize = 8.f;

EditorToolbox::EditorToolbox() :
  m_tileset(*Level::current()->get_tileset()),
  m_collapsed(false),
  m_hovered_tile(-1),
  m_selected_tile(-1)
{
}

EditorToolbox::~EditorToolbox()
{
}


void
EditorToolbox::draw(const RenderContext& context)
{
  const float height = m_collapsed ? 0.f : s_height;

  // Draw toolbox background and collapse bar.
  if (!m_collapsed)
  {
    context.draw_filled_rect(0, 0, context.get_width(), height, Resources::Colors::GRAY);
  }
  context.draw_filled_rect(0, height, context.get_width(), s_collapse_bar_height, Resources::Colors::BLACK);

  if (!m_collapsed) // Draw toolbox contents, only if it's not collapsed.
  {
    // Draw tiles on toolbox.
    float drawn_width = TILE_WIDTH_DEFAULT;
    for (int i = 0; i < static_cast<int>(m_tileset.get_tile_entries().size()); i++)
    {
      const float pos_offset = (i == m_hovered_tile ? s_hover_resize / 2 : 0);
      const float size_offset = (i == m_hovered_tile ? s_hover_resize : 0);
      const Rectf tile_rect(drawn_width - pos_offset, s_height / 2 - TILE_WIDTH_DEFAULT / 2 - pos_offset,
                            TILE_WIDTH_DEFAULT + size_offset, TILE_WIDTH_DEFAULT + size_offset);

      context.draw_texture(m_tileset.get_tile_texture(i), tile_rect);
      if (i == m_selected_tile) // Draw frame, if tile is selected.
        context.draw_rect(tile_rect.grown(1), Resources::Colors::YELLOW);

      drawn_width += TILE_WIDTH_DEFAULT * 2;
    }
  }

  // Draw collapse/uncollapse bar.
  if (!m_collapsed)
  {
    context.draw_line(0, height, context.get_width(), height, Resources::Colors::WHITE);
  }
  context.draw_text(Resources::Fonts::DEFAULT, m_collapsed ? "v" : "^",
                    context.get_width() / 2, height - s_collapse_bar_height / 2,
                    ALIGN_CENTER, Resources::Colors::WHITE);
}


bool
EditorToolbox::process_mouse_motion(const SDL_MouseMotionEvent& motion)
{
  m_hovered_tile = -1;
  if (motion.y > (m_collapsed ? 0.f : s_height) + s_collapse_bar_height)
    return false; // Not hovering the toolbox, or the collapse bar, if collapsed.

  // Not hovering the tiles bar.
  if (!(motion.y >= s_height / 2 - TILE_WIDTH_DEFAULT / 2 &&
        motion.y <= s_height / 2 + TILE_WIDTH_DEFAULT / 2)) return true;

  // Detect if the mouse is hovering any tile.
  float tile_check_x = TILE_WIDTH_DEFAULT * 2;
  int tile_check_index = -1;
  while (tile_check_x <= SCREEN_WIDTH)
  {
    tile_check_index++;
    if (motion.x >= tile_check_x - TILE_WIDTH_DEFAULT &&
        motion.x <= tile_check_x) break;
    tile_check_x += TILE_WIDTH_DEFAULT * 2;
  }

  // Set the selected tile.
  if (tile_check_index > -1 &&
      tile_check_index < static_cast<int>(m_tileset.get_tile_entries().size()))
  {
    m_hovered_tile = tile_check_index;
  }
  return true;
}

bool
EditorToolbox::process_mouse_down(const SDL_MouseButtonEvent& button)
{
  if (m_collapsed)
  {
    if (button.y > s_collapse_bar_height) return false; // Not hovering the collapse bar.

    // Uncollapse the toolbox.
    m_collapsed = false;
    return true;
  }

  if (button.y > s_height + s_collapse_bar_height) return false; // Not hovering the toolbox, or the collapse bar.

  if (button.y > s_height) // Hovering the collapse bar.
  {
    // Collapse the toolbox.
    m_collapsed = true;
    return true;
  }

  if (m_hovered_tile < 0) return true; // No tile is hovered.

  // Select the hovered tile.
  m_selected_tile = m_hovered_tile;
  Editor::current()->get_widget<EditorOverlay>()->set_selected_tile(&m_tileset.get_tile_entry(m_selected_tile));
  return true;
}
