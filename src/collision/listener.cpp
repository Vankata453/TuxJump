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

#include "collision/listener.hpp"

#include "collision/manager.hpp"

CollisionListener::CollisionListener(const Rectf rect) :
  CollisionEntity(std::move(rect)),
  m_col_manager(CollisionManager::current())
{
}

CollisionListener::~CollisionListener()
{
}

void
CollisionListener::update()
{
  m_collides = false;

  for (auto* obj : m_col_manager.get_objects())
  {
    const CollisionType col = obj->collision(m_rect);
    if (col == COLLISION_NONE) continue;

    m_collides = true;
    switch (col)
    {
      case COLLISION_TOP:
        collision_top(obj);
        break;
      case COLLISION_BOTTOM:
        collision_bottom(obj);
        break;
      case COLLISION_LEFT:
        collision_left(obj);
        break;
      case COLLISION_RIGHT:
        collision_right(obj);
        break;
    }
  }

  if (!m_collides) collision_none();
}
