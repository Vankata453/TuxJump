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

#ifndef TUXJUMP_COLLISION_MANAGER_HEADER
#define TUXJUMP_COLLISION_MANAGER_HEADER

#include "util/current_object.hpp"

#include "collision/object.hpp"

// A class to store all active collision objects.
class CollisionManager final : public CurrentObject<CollisionManager>
{
public:
  typedef std::vector<CollisionObject*> CollisionObjects;

private:
  CollisionObjects m_col_objects;

public:
  CollisionManager();
  ~CollisionManager();

  void add_object(CollisionObject* obj);
  void remove_object(const int id);

  // Get properties
  const CollisionObjects& get_objects() { return m_col_objects; }

private:
  CollisionManager(const CollisionManager&) = delete;
  CollisionManager& operator=(const CollisionManager&) = delete;
};

#endif
