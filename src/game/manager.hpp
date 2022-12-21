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


// The GameManager is the root to the management of main game events.
// EXAMPLES: Drawing content on screen and processing events.
// GameManager also manages the current game mode.

#ifndef TUXJUMP_GAME_MANAGER_HEADER
#define TUXJUMP_GAME_MANAGER_HEADER

#include "util/current_object.hpp"

#include <memory>
#include <vector>

#include "control/manager.hpp"
#include "game/config.hpp"
#include "game/mode.hpp"

class GameManager final : public CurrentObject<GameManager>
{
private:
  // The interval in which game ticks should occur.
  static const uint32_t s_tick_interval;

private:
  enum ScheduledAction
  {
    ACTION_START_GAME,
    ACTION_EXIT_GAME
  };

private:
  // Indicate if the application should close.
  bool m_quit;

  // Store the next tick the game loop should resume in.
  uint32_t m_next_tick;

  // Store the current game mode.
  std::unique_ptr<GameMode> m_game_mode;

  // Scheduled actions to be performed.
  std::vector<ScheduledAction> m_scheduled_actions;

  // Store other important instances.
  SDL_Window* m_window;
  std::unique_ptr<RenderContext> m_render_context;
  SDL_Event m_event_handler;
  std::unique_ptr<ControlManager> m_control_manager;
  std::unique_ptr<GameConfig> m_game_config;

public:
  GameManager();
  ~GameManager();

  void main_loop();

  // Game mode management
  void start_game() { m_scheduled_actions.push_back(ACTION_START_GAME); }
  void exit_game() { m_scheduled_actions.push_back(ACTION_EXIT_GAME); }
  void quit_game() { m_quit = true; }

private:
  void draw(const RenderContext& context);
  void process_event();

  void update();

private:
  GameManager(const GameManager&) = delete;
  GameManager& operator=(const GameManager&) = delete;
};

#endif
