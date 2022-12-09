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
// GameManager also manages the current GameMode.

#include "game/manager.hpp"

#include <iostream>

#include "game/resources.hpp"
#include "game/session.hpp"
#include "gui/menu_manager.hpp"

GameManager::GameManager() :
  m_quit(false),
  m_game_mode(),
  m_scheduled_actions()
{
  exit_game(); // Schedule an action to start up the main menu.
  update();
}

GameManager::~GameManager()
{
}

void
GameManager::draw(RenderContext& context)
{
  update();

  try
  {
    m_game_mode->draw(context);
  }
  catch (std::exception& err)
  {
    // Catch fatal errors
    std::cout << err.what() << std::endl;
    quit_game();
  }
}

void
GameManager::process_event(SDL_Event& ev)
{
  try
  {
    m_game_mode->process_event(ev);
  }
  catch (std::exception& err)
  {
    // Catch fatal errors
    std::cout << err.what() << std::endl;
    quit_game();
  }
}

void
GameManager::update()
{
  // Process potential scheduled actions.
  for (const ScheduledAction& action : m_scheduled_actions)
  {
    switch (action)
    {
      case ACTION_EXIT_GAME:
      {
        m_game_mode.reset(new MenuManager);
        break;
      }
      case ACTION_START_GAME:
      {
        m_game_mode.reset(new GameSession);
        break;
      }
    }
  }

  m_scheduled_actions.clear();
}
