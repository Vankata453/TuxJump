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

#ifndef TUXJUMP_UTIL_UNIQUE_OBJECT_HEADER
#define TUXJUMP_UTIL_UNIQUE_OBJECT_HEADER

// Represents an object, which has a unique ID attached to it.
class UniqueObject
{
private:
  static int s_id_counter;

private:
  const int m_id;

public:
  UniqueObject();
  ~UniqueObject();

  // Get properties
  const int& get_id() const { return m_id; }

private:
  UniqueObject(const UniqueObject&) = delete;
  UniqueObject& operator=(const UniqueObject&) = delete;
};

#endif
