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

#ifndef TUXJUMP_GAME_SESSION_HEADER
#define TUXJUMP_GAME_SESSION_HEADER

#include "video/render_context.hpp"
#include "game/player.hpp"
#include "level/level.hpp"

class GameSession final
{
private:
  static const float s_game_speed;

private:
  std::unique_ptr<Level> m_level;
  std::unique_ptr<Player> m_player;

  float m_progress;

public:
  GameSession();
  ~GameSession();

  void draw(RenderContext& context);
  void process_event(SDL_Event& ev);

private:
  GameSession(const GameSession&) = delete;
  GameSession& operator=(const GameSession&) = delete;
};

#endif
