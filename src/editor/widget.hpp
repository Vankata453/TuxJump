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

#ifndef TUXJUMP_EDITOR_WIDGET_HEADER
#define TUXJUMP_EDITOR_WIDGET_HEADER

#include "video/render_context.hpp"

class EditorWidget
{
public:
  EditorWidget() {}
  virtual ~EditorWidget() = default;

  virtual void draw(const RenderContext& context) = 0;
  virtual void update() {}

  virtual bool process_mouse_motion(const SDL_MouseMotionEvent& motion) { return false; }
  virtual bool process_mouse_down(const SDL_MouseButtonEvent& button) { return false; }
  virtual bool process_mouse_up(const SDL_MouseButtonEvent& button) { return false; }

private:
  EditorWidget(const EditorWidget&) = delete;
  EditorWidget& operator=(const EditorWidget&) = delete;
};

#endif
