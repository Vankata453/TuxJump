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

const float EditorToolbox::s_reserved_for_tiles = 0.8f;
const float EditorToolbox::s_hover_resize = 8.f;

const std::vector<EditorToolbox::Option> EditorToolbox::s_options =
  {
    { "Resize", []() { Level::current()->resize(-14, -9); } },
    { "Save", []() {} },
    { "More...", []() {} }
  };

EditorToolbox::EditorToolbox() :
  m_tileset(*Level::current()->get_tileset()),
  m_collapsed(false),
  m_hovered_tile(-1),
  m_selected_tile(-1),
  m_hovered_option(-1)
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
    const float tile_section_width = s_reserved_for_tiles * context.get_width();
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
      if (drawn_width >= tile_section_width)
        break; // Break the loop, if the tile section limit is reached.
    }

    // Draw line between sections.
    const float separation_x = tile_section_width + 5.f;
    context.draw_line(separation_x, 0, separation_x, s_height, Resources::Colors::BLACK);

    // Draw options on toolbox.
    const float options_section_x = separation_x + 1.f;
    const float option_spacing = s_height / (static_cast<int>(s_options.size()) * 2);
    float drawn_height = 0.f;
    for (int i = 0; i < static_cast<int>(s_options.size()); i++)
    {
      // Draw option background, if hovered.
      if (i == m_hovered_option)
        context.draw_filled_rect(options_section_x, drawn_height,
                                 context.get_width() - options_section_x, option_spacing * 2,
                                 Resources::Colors::WHITE);
      // Draw option text.
      context.draw_text(Resources::Fonts::DEFAULT, s_options.at(i).name,
                        options_section_x + (context.get_width() - options_section_x) / 2,
                        drawn_height + option_spacing,
                        ALIGN_CENTER, Resources::Colors::BLACK);
      // Draw line to separate options.
      const float option_line_y = drawn_height + option_spacing * 2;
      context.draw_line(separation_x, option_line_y,
                        context.get_width(), option_line_y, Resources::Colors::BLACK);

      drawn_height += s_height / static_cast<int>(s_options.size());
    }
  }

  // Draw collapse/uncollapse bar.
  if (!m_collapsed)
  {
    context.draw_line(0, height, context.get_width(), height, Resources::Colors::WHITE);
  }
  context.draw_text(Resources::Fonts::DEFAULT, m_collapsed ? "v" : "^",
                    context.get_width() / 2, height + s_collapse_bar_height / 2,
                    ALIGN_CENTER, Resources::Colors::WHITE);
}


bool
EditorToolbox::process_mouse_motion(const SDL_MouseMotionEvent& motion)
{
  m_hovered_tile = -1;
  m_hovered_option = -1;

  if (motion.y > (m_collapsed ? 0.f : s_height) + s_collapse_bar_height)
    return false; // Not hovering the toolbox, or the collapse bar, if collapsed.

  const float tile_section_width = s_reserved_for_tiles * SCREEN_WIDTH;
  if (motion.x <= tile_section_width) // Mouse is in the tiles section.
  {
    // Not hovering the tiles bar.
    if (!(motion.y >= s_height / 2 - TILE_WIDTH_DEFAULT / 2 &&
        motion.y <= s_height / 2 + TILE_WIDTH_DEFAULT / 2)) return true;

    // Detect if the mouse is hovering any tile.
    float tile_check_x = TILE_WIDTH_DEFAULT * 2;
    int tile_check_index = -1;
    while (tile_check_x < tile_section_width)
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
  }
  else // Mouse is in the options section.
  {
    // Detect the option the mouse is hovering.
    const float option_distance = s_height / static_cast<int>(s_options.size());
    float option_check_y = 0.f;
    int option_check_index = -1;
    while (option_check_y <= s_height)
    {
      option_check_index++;
      if (motion.y >= option_check_y &&
          motion.y <= option_check_y + option_distance) break;
      option_check_y += option_distance;
    }
    // Set the selected option.
    if (option_check_index > -1 &&
        option_check_index < static_cast<int>(s_options.size()))
    {
      m_hovered_option = option_check_index;
    }
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

  if (m_hovered_tile > -1) // A tile is being hovered.
  {
    // Select the hovered tile.
    m_selected_tile = m_hovered_tile;
    Editor::current()->get_widget<EditorOverlay>()->set_selected_tile(&m_tileset.get_tile_entry(m_selected_tile));
  }
  else if (m_hovered_option > -1) // An option is being hovered.
  {
    // Execute the action of the hovered option.
    s_options.at(m_hovered_option).action();
  }
  return true;
}
