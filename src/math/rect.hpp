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

#ifndef TUXJUMP_MATH_RECT_HEADER
#define TUXJUMP_MATH_RECT_HEADER

#include <SDL2/SDL.h>

#include <string>

class Position
{
public:
  int x;
  int y;

  Position(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
  ~Position() {}

  virtual std::string to_string() const { return x + " " + y; }
};

class Positionf
{
public:
  float x;
  float y;

  Positionf(float x_ = 0.0f, float y_ = 0.0f) : x(x_), y(y_) {}
  ~Positionf() {}

  virtual std::string to_string() const { return std::to_string(x) + " " + std::to_string(y); }
};


class Size
{
public:
  int w;
  int h;

  Size(int w_ = 0, int h_ = 0) : w(w_), h(h_) {}
  ~Size() {}

  virtual std::string to_string() const { return w + " " + h; }
};

class Sizef
{
public:
  float w;
  float h;

  Sizef(float w_ = 0.0f, float h_ = 0.0f) : w(w_), h(h_) {}
  ~Sizef() {}

  virtual std::string to_string() const { return std::to_string(w) + " " + std::to_string(h); }
};


class Rect final : public Position,
                   public Size
{
public:
  Rect(int x_ = 0, int y_ = 0, int w_ = 0, int h_ = 0) : Position(x_, y_), Size(w_, h_) {}
  ~Rect() {}

  virtual std::string to_string() const override { return Position::to_string() + " " + Size::to_string(); }
  SDL_Rect to_sdl() const { return { x, y, w, h }; }
};

class Rectf final : public Positionf,
                    public Sizef
{
public:
  Rectf(float x_ = 0.0f, float y_ = 0.0f, float w_ = 0.0f, float h_ = 0.0f) : Positionf(x_, y_), Sizef(w_, h_) {}
  ~Rectf() {}

  virtual std::string to_string() const override { return Positionf::to_string() + " " + Sizef::to_string(); }
  SDL_FRect to_sdl() const { return { x, y, w, h }; }
};

#endif
