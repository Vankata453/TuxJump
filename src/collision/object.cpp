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

#include "collision/util.hpp"

CollisionObject::CollisionObject(const Rectf& rect) :
  CollisionEntity(rect)
{
}

CollisionObject::~CollisionObject()
{
}


CollisionType
CollisionObject::collision(const Rectf& t)
{
  CollisionType col = CollisionUtil::collision(m_rect, t);
  m_collides = (col != COLLISION_NONE);
  return col;
}
