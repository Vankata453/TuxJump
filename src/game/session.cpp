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

#include "game/session.hpp"

#include "control/manager.hpp"
#include "game/manager.hpp"

const float GameSession::s_game_speed = 0.05f;

GameSession::GameSession() :
  m_col_manager(new CollisionManager()),
  m_level(new Level("data/levels/test.tjl")),
  m_player(new Player())
{
}

GameSession::~GameSession()
{
}

void
GameSession::draw(RenderContext& context)
{
  m_level->draw(context);

  m_player->update();
  m_player->draw(context);

  m_level->apply_offset(s_game_speed);
}

void
GameSession::process_event(SDL_Event& ev)
{
  switch (ev.type)
  {
    case SDL_KEYDOWN:
    {
      switch (ev.key.keysym.sym)
      {
        case SDLK_ESCAPE:
          GameManager::current()->exit_game();
          break;
        default:
          m_player->process_action(ControlManager::current()->get_action(ev.key.keysym.sym));
          break;
      }
    }
  }
}
