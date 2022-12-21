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
#include "game/global.hpp"
#include "game/manager.hpp"

const float GameSession::s_game_speed = GAME_FPS * 0.001f;

GameSession::GameSession() :
  m_col_manager(new CollisionManager()),
  m_level(new Level("levels/test.tjl")),
  m_player(new Player()),
  m_progress(0.0f)
{
}

GameSession::~GameSession()
{
}

void
GameSession::draw(const RenderContext& context)
{
  // Draw level background and interactive layers.
  m_level->draw_background(context);
  m_level->draw(context, TileMap::LAYER_BACKGROUND, m_progress, 0.0f);
  m_level->draw(context, TileMap::LAYER_INTERACTIVE, m_progress, 0.0f);

  m_player->update(m_progress, 0.0f);
  m_player->draw(context);

  // Draw level foreground.
  m_level->draw(context, TileMap::LAYER_FOREGROUND, m_progress, 0.0f);

  m_progress += s_game_speed;
}

void
GameSession::process_event(const SDL_Event& ev)
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
