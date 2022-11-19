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

#include "game/resources.hpp"

const float GameSession::s_game_speed = 0.05f;

GameSession::GameSession() :
  m_level(new Level("data/levels/test.tjl")),
  m_player(new Player()),
  m_progress(0.0f)
{
}

GameSession::~GameSession()
{
}

void
GameSession::draw(RenderContext& context)
{
  context.set_offset_x(m_progress);
  m_level->draw(context);
  context.clear_offset_x();

  m_player->update();
  m_player->draw(context);

  m_progress += s_game_speed;
}

void
GameSession::process_event(SDL_Event& ev)
{
  m_player->process_event(ev);
}
