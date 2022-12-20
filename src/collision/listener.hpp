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

#ifndef TUXJUMP_COLLISION_LISTENER_HEADER
#define TUXJUMP_COLLISION_LISTENER_HEADER

#include "collision/entity.hpp"

class CollisionManager;
class CollisionObject;
class Level;

// A class to actively check for collision with tiles and objects on update.
class CollisionListener : public CollisionEntity
{
private:
  CollisionManager& m_col_manager;
  Level& m_level;

public:
  CollisionListener(const Rectf& rect);
  ~CollisionListener();

  virtual void update(const float& x_offset, const float& y_offset);

protected:
  // Collision events
  virtual void collision_top(CollisionObject* obj) {}
  virtual void collision_bottom(CollisionObject* obj) {}
  virtual void collision_left(CollisionObject* obj) {}
  virtual void collision_right(CollisionObject* obj) {}
  virtual void collision_none() {}

private:
  CollisionListener(const CollisionListener&) = delete;
  CollisionListener& operator=(const CollisionListener&) = delete;
};

#endif
