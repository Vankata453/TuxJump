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

#ifndef TUXJUMP_COLLISION_OBJECT_HEADER
#define TUXJUMP_COLLISION_OBJECT_HEADER

#include "collision/entity.hpp"
#include "util/unique_object.hpp"

#include <vector>

#include "collision/type.hpp"

// Represents a unique object which collision can occur with.
class CollisionObject : public CollisionEntity,
                        public UniqueObject
{
public:
  CollisionObject(const Rectf& rect);
  ~CollisionObject();

  CollisionType collision(const Rectf& t);

private:
  CollisionObject(const CollisionObject&) = delete;
  CollisionObject& operator=(const CollisionObject&) = delete;
};

#endif
