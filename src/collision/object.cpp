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

#include "collision/object.hpp"

#include "collision/manager.hpp"
#include "game/global.hpp"

CollisionObject::CollisionObject(const Rectf& rect) :
  UniqueObject(),
  CollisionEntity(rect)
{
  if (CollisionManager::current())
    CollisionManager::current()->add_object(this);
  else
    Log::warning("CollisionObject created, but not added to CollisionManager.");
}

CollisionObject::~CollisionObject()
{
  if (CollisionManager::current())
    CollisionManager::current()->remove_object(get_id());
}

CollisionType
CollisionObject::collision(const Rectf& t)
{
  if (m_rect.x < 0 || m_rect.x > SCREEN_WIDTH || m_rect.y < 0 || m_rect.y > SCREEN_HEIGHT)
    return COLLISION_NONE; // Do not perform checks if object is out of screen bounds.

  const Rectf& s = m_rect;
  m_collides = true;

  const bool x_match_left = t.x >= s.x && t.x <= s.x + s.w;
  const bool x_match_right = t.x + t.w >= s.x && t.x + t.w <= s.x + s.w;
  const bool y_match_top = t.y >= s.y && t.y <= s.y + s.h;
  const bool y_match_bottom = t.y + t.h >= s.y && t.y + t.h <= s.y + s.h;

  if (x_match_left || x_match_right)
  {
    if (y_match_top && std::ceil(t.y + t.h) >= s.y + s.h * 2)
      return COLLISION_TOP;
    else if (y_match_bottom && std::floor(t.y) <= s.y - s.h)
      return COLLISION_BOTTOM;
  }

  if (y_match_top || y_match_bottom)
  {
    if (x_match_left)
      return COLLISION_LEFT;
    else if (x_match_right)
      return COLLISION_RIGHT;
  }

  m_collides = false;
  return COLLISION_NONE;
}
