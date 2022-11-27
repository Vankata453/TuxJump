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

#include "level/tile.hpp"

const float Tile::s_width = 32.0f;

Tile::Tile(const int& id, int x, int y) :
  CollisionObject({ x * s_width, y * s_width, s_width, s_width }),
  m_id(id)
{
}

Tile::~Tile()
{
}

void
Tile::apply_offset(const float& offset)
{
  m_rect.x -= offset;
}
