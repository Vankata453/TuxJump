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

GameManager::GameManager(SDL_Window* window) :
  m_quit(false),
  m_game_mode(),
  m_scheduled_actions(),
  m_render_context(window),
  m_event_handler(),
  m_control_manager(),
  m_game_config()
{
  try
  {
    // Perform required initializations.
    Resources::Fonts::init_fonts();
  }
  catch (std::exception& err)
  {
    // Catch fatal errors.
    std::cout << err.what() << std::endl;
    quit_game();
    return;
  }

  exit_game(); // Schedule an action to start up the main menu.
  update();
}

GameManager::~GameManager()
{
  // Perform required destructions.
  Resources::Fonts::close_fonts();
}

void
GameManager::main_loop()
{
  // Main game loop
  while (!m_quit)
  {
    try
    {
      // Process events, if any.
      if (SDL_PollEvent(&m_event_handler) != 0)
      {
        if (m_event_handler.type == SDL_QUIT) // Quit registered by SDL
        {
          quit_game();
        }
        else
        {
          process_event();
        }
      }

      // Draw content on screen.
      m_render_context.render_clear();
      draw();
      m_render_context.render_present();
    }
    catch (std::exception& err)
    {
      // Catch fatal errors.
      std::cout << err.what() << std::endl;
      break;
    }
  }
}

void
GameManager::draw()
{
  update();
  m_game_mode->draw(m_render_context);
}

void
GameManager::process_event()
{
  m_game_mode->process_event(m_event_handler);
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
