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

#ifndef TUXJUMP_EDITOR_OVERLAY_HEADER
#define TUXJUMP_EDITOR_OVERLAY_HEADER

#include "editor/widget.hpp"

#include "level/tileset.hpp"

class EditorOverlay final : public EditorWidget
{
private:
  const int& m_width;
  const int& m_height;
  const Positionf& m_pos;

  bool m_inserting_tiles;
  const TileSet::TileEntry* m_selected_tile;
  Position m_preview_coords;

public:
  EditorOverlay();
  ~EditorOverlay();

  void draw(const RenderContext& context) override;
  void update() override;

  bool process_mouse_motion(const SDL_MouseMotionEvent& motion) override;
  bool process_mouse_down(const SDL_MouseButtonEvent& button) override;
  bool process_mouse_up(const SDL_MouseButtonEvent& button) override;

  void insert_tile();

  // Set properties
  void set_selected_tile(const TileSet::TileEntry* tile) { m_selected_tile = tile; }

private:
  EditorOverlay(const EditorOverlay&) = delete;
  EditorOverlay& operator=(const EditorOverlay&) = delete;
};

#endif
