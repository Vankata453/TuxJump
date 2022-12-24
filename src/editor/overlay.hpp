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

class RenderContext;

class EditorOverlay final
{
private:
  static const float s_grid_width;

public:
  EditorOverlay();
  ~EditorOverlay();

  void draw(const RenderContext& context);
  void process_event(const SDL_Event& ev);

private:
  EditorOverlay(const EditorOverlay&) = delete;
  EditorOverlay& operator=(const EditorOverlay&) = delete;
};

#endif
