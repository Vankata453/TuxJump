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

#ifndef TUXJUMP_GAME_PLAYER_HEADER
#define TUXJUMP_GAME_PLAYER_HEADER

#include "collision/listener.hpp"

#include "control/control.hpp"
#include "video/render_context.hpp"

class Player final : public CollisionListener
{
private:
  static const float s_default_spawn_height;
  static const float s_max_jump_height;
  static const float s_jump_speed;
  static const float s_gravity_speed;

  static const std::string s_image_file;

private:
  float m_jump_height;

public:
  Player();
  ~Player();

  void draw(RenderContext& context) override;
  void process_action(ControlAction action);

  // Player actions
  void kill();

private:
  // Collision events
  void collision_top(CollisionObject* obj) override;
  void collision_bottom(CollisionObject* obj) override;
  void collision_left(CollisionObject* obj) override;
  void collision_right(CollisionObject* obj) override;
  void collision_none() override;

  // Player physics
  void jump();
  bool update_jump();

private:
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
};

#endif
