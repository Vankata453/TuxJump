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

#include "game/manager.hpp"
#include "game/resources.hpp"
#include "level/level.hpp"

const float Player::s_default_spawn_height = 300.0f;
const float Player::s_max_jump_height = 100.0f;
const float Player::s_jump_speed = 0.15f;
const float Player::s_gravity_speed = 0.1f;

const std::string Player::s_image_file = "data/images/tux.png";


Player::Player() :
  CollisionListener({ 150, Level::current()->get_data().spawn_height, 0, 0 }),
  m_jump_height(0.0f)
{
  // Set up width and height, according to texture.
  SDL_Texture* texture = TextureManager::current()->load_image(s_image_file);
  Sizef texture_size = TextureManager::current()->get_sizef(texture);
  m_rect.w = texture_size.w;
  m_rect.h = texture_size.h;

  if (m_rect.y < 0.0f) // Spawn height not set
    m_rect.y = s_default_spawn_height;
}

Player::~Player()
{
}

void
Player::draw(RenderContext& context)
{
  context.draw_image(s_image_file, m_rect);

  CollisionEntity::draw(context); // Draw collision rect.
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

// Player actions

void
Player::kill()
{
  GameManager::current()->exit_game(); // Temporary (TODO)
}

// Collision events

void
Player::collision_top(CollisionObject* obj)
{
  m_jump_height = 0.0f;
  m_rect.y += s_gravity_speed;
}

void
Player::collision_bottom(CollisionObject* obj)
{
  m_jump_height = 0.0f;
  update_jump();
}

void
Player::collision_left(CollisionObject* obj)
{
  kill();
}

void
Player::collision_right(CollisionObject* obj)
{
  kill();
}

void
Player::collision_none()
{
  if (!update_jump())
  {
    m_rect.y += s_gravity_speed;
    m_jump_height = -1.0f;
  }
}

// Player physics

void
Player::jump()
{
  if (m_jump_height != 0.0f) return;

  m_jump_height = s_jump_speed;
  m_rect.y -= s_jump_speed;
}

bool
Player::update_jump()
{
  if (m_jump_height <= 0.0f) return false;
  if (m_jump_height >= s_max_jump_height)
  {
    m_jump_height = 0.0f;
    return false;
  }

  m_jump_height += s_jump_speed;
  m_rect.y -= s_jump_speed;

  return true;
}
