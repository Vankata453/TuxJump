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

#ifndef TUXJUMP_EDITOR_TOOLBOX_HEADER
#define TUXJUMP_EDITOR_TOOLBOX_HEADER

#include "editor/widget.hpp"

class TileSet;

class EditorToolbox final : public EditorWidget
{
private:
  static const float s_height;
  static const float s_collapse_bar_height;
  static const float s_hover_resize;

private:
  const TileSet& m_tileset;
  bool m_collapsed;
  int m_hovered_tile;
  int m_selected_tile;

public:
  EditorToolbox();
  ~EditorToolbox();

  void draw(const RenderContext& context) override;

  bool process_mouse_motion(const SDL_MouseMotionEvent& motion) override;
  bool process_mouse_down(const SDL_MouseButtonEvent& button) override;

private:
  EditorToolbox(const EditorToolbox&) = delete;
  EditorToolbox& operator=(const EditorToolbox&) = delete;
};

#endif
