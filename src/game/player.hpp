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

#ifndef TUXJUMP_GAME_PLAYER_HEADER
#define TUXJUMP_GAME_PLAYER_HEADER

#include "video/render_context.hpp"

class Player final
{
private:
  static const float s_default_spawn_height;
  static const float s_max_jump_height;
  static const float s_jump_speed;

private:
  float m_height;
  float m_jump_height;
  bool m_stop_jump;

public:
  Player();
  ~Player();

  void draw(RenderContext& context);
  void update();
  void process_event(SDL_Event& ev);

private:
  // Player physics
  void jump();
  void update_jump();

private:
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
};

#endif
