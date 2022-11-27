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
// GameManager also stores important variables and instances for the game to function.

#ifndef TUXJUMP_GAME_MANAGER_HEADER
#define TUXJUMP_GAME_MANAGER_HEADER

#include "util/current_object.hpp"

#include <memory>

#include "video/render_context.hpp"
#include "game/session.hpp"
#include "gui/menu_manager.hpp"

class GameManager final : public CurrentObject<GameManager>
{
private:
  enum GameMode
  {
    MODE_MENU,
    MODE_GAME
  };

private:
  // Store important to the game variables and instances
  std::unique_ptr<MenuManager> m_menu_manager;
  std::unique_ptr<GameSession> m_game_session;

  GameMode m_mode; // Current game mode

  // Scheduled actions to be performed
  bool m_start_game;
  bool m_exit_game;
  bool m_quit;

public:
  GameManager();
  ~GameManager();

  void draw(RenderContext& context);
  void process_event(SDL_Event& ev);

  // Game mode management
  void start_game() { m_start_game = true; }
  void exit_game() { m_exit_game = true; }
  void quit_game() { m_quit = true; }

  // Get properties
  bool quit_requested() const { return m_quit; }

private:
  void update();

private:
  GameManager(const GameManager&) = delete;
  GameManager& operator=(const GameManager&) = delete;
};

#endif
