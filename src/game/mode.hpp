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

#ifndef TUXJUMP_GAME_MODE_HEADER
#define TUXJUMP_GAME_MODE_HEADER

#include "video/render_context.hpp"

class GameMode
{
public:
  GameMode() {}
  virtual ~GameMode() = default;

  virtual void draw(RenderContext& context) {}
  virtual void process_event(SDL_Event& ev) {}

private:
  GameMode(const GameMode&) = delete;
  GameMode& operator=(const GameMode&) = delete;
};

#endif