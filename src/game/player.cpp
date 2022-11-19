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

#include "game/player.hpp"

#include "game/global.hpp"
#include "game/resources.hpp"
#include "level/level.hpp"

const float Player::s_default_spawn_height = 300.0f;
const float Player::s_max_jump_height = 100.0f;
const float Player::s_jump_speed = 0.15f;

Player::Player() :
  m_height(Level::current().get_spawn_height()),
  m_jump_height(0.0f),
  m_stop_jump(false)
{
  if (m_height < 0.0f) // Spawn height not set
    m_height = s_default_spawn_height;
}

Player::~Player()
{
}

void
Player::draw(RenderContext& context)
{
  context.draw_image("data/images/tux.png", context.get_width() * 0.15,
                      m_height - m_jump_height, 40, 40);
}

void
Player::update()
{
  update_jump();
}

void
Player::process_event(SDL_Event& ev)
{
  switch (ev.type)
  {
    case SDL_KEYDOWN:
    {
      switch (ev.key.keysym.sym)
      {
        case SDLK_SPACE:
        case SDLK_UP:
          jump();
          break;
      }
    }
  }
}

// Player physics

void
Player::jump()
{
  if (m_jump_height > 0.0f) return;

  m_stop_jump = false;
  m_jump_height += s_jump_speed;
}

void
Player::update_jump()
{
  if (m_jump_height <= 0.0f) return;

  if (m_jump_height >= s_max_jump_height) m_stop_jump = true;
  m_jump_height += s_jump_speed * (m_stop_jump ? -1.0f : 1.0f);
}
