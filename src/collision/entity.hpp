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

#ifndef TUXJUMP_COLLISION_ENTITY_HEADER
#define TUXJUMP_COLLISION_ENTITY_HEADER

#include "video/render_context.hpp"

// Represents an entity, which is involved in collision detection.
class CollisionEntity
{
protected:
  Rectf m_rect;
  bool m_collides;

public:
  CollisionEntity(const Rectf rect);
  ~CollisionEntity();

  virtual void draw(RenderContext& context);

  // Get properties
  const Rectf& get_rect() const { return m_rect; }

private:
  CollisionEntity(const CollisionEntity&) = delete;
  CollisionEntity& operator=(const CollisionEntity&) = delete;
};

#endif
