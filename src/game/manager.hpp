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

#include "game/mode.hpp"

class GameManager final : public CurrentObject<GameManager>
{
private:
  enum ScheduledAction
  {
    ACTION_START_GAME,
    ACTION_EXIT_GAME
  };

private:
  // Indicate if the application should close.
  bool m_quit;

  // Store the current game mode.
  std::unique_ptr<GameMode> m_game_mode;

  // Scheduled actions to be performed.
  std::vector<ScheduledAction> m_scheduled_actions;

public:
  GameManager();
  ~GameManager();

  void draw(RenderContext& context);
  void process_event(SDL_Event& ev);

  // Game mode management
  void start_game() { m_scheduled_actions.push_back(ACTION_START_GAME); }
  void exit_game() { m_scheduled_actions.push_back(ACTION_EXIT_GAME); }
  void quit_game() { m_quit = true; }

  // Get properties
  const bool& quit_requested() const { return m_quit; }

private:
  void update();

private:
  GameManager(const GameManager&) = delete;
  GameManager& operator=(const GameManager&) = delete;
};

#endif
