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

#ifndef TUXJUMP_UTIL_CURRENT_OBJECT_HEADER
#define TUXJUMP_UTIL_CURRENT_OBJECT_HEADER

#include "util/log.hpp"

// Allows global access to unique "current" instances of classes.
template<class C>
class CurrentObject
{
private:
  static CurrentObject<C>* s_current;

public:
  static C* current()
  {
    return static_cast<C*>(s_current);
  }

public:
  CurrentObject()
  {
    if (s_current)
    {
      Log::fatal("CurrentObject initialization error: Object already exists.");
    }
    s_current = this;
  }
  virtual ~CurrentObject()
  {
    s_current = nullptr;
  }
};

template<typename T>
CurrentObject<T>* CurrentObject<T>::s_current = nullptr;

#endif
