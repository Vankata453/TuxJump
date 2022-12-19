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
#include "util/file_system.hpp"

const uint32_t GameManager::s_tick_interval = 1000 / GAME_FPS;

GameManager::GameManager() :
  m_quit(false),
  m_next_tick(),
  m_game_mode(),
  m_scheduled_actions(),
  m_window(),
  m_render_context(),
  m_event_handler(),
  m_control_manager(),
  m_game_config()
{
  try
  {
    // Perform required initializations.
    FileSystem::init();
    m_control_manager.reset(new ControlManager());
    m_game_config.reset(new GameConfig());

    // Intialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      Log::fatal("SDL could not initialize! SDL_Error: ", SDL_GetError());
    }
    // Create SDL window.
    m_window = SDL_CreateWindow((GAME_TITLE + (GAME_DEV_BUILD ? " [DEVELOPMENT BUILD]" : "")).c_str(),
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_window == NULL)
    {
			Log::fatal("Window could not be created! SDL_Error: ", SDL_GetError());
    }

    m_render_context.reset(new RenderContext(m_window));
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
  try
  {
    // Perform required destructions.
    Resources::Fonts::close_fonts();
    m_render_context.reset();

    SDL_DestroyWindow(m_window); // Destroy SDL window.
    SDL_Quit(); // Quit SDL.

    m_game_config.reset();
    m_control_manager.reset();
    FileSystem::deinit();
  }
  catch (std::exception& err)
  {
    // Catch fatal errors.
    std::cout << err.what() << std::endl;
    quit_game();
    return;
  }
}

void
GameManager::main_loop()
{
  // Initialize the next tick.
  m_next_tick = SDL_GetTicks() + s_tick_interval;

  // References to variables for convenience.
  RenderContext& context = *m_render_context;

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
      context.render_clear();
      draw(context);
      context.render_present();
    }
    catch (std::exception& err)
    {
      // Catch fatal errors.
      std::cout << err.what() << std::endl;
      break;
    }

    // Wait for the next tick to accomplish a tick interval.
    const uint32_t current_tick = SDL_GetTicks();
    if (current_tick < m_next_tick)
      SDL_Delay(m_next_tick - current_tick);
    m_next_tick += s_tick_interval;
  }
}

void
GameManager::draw(RenderContext& context)
{
  update();
  m_game_mode->draw(context);
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
        m_game_mode.reset(new MenuManager());
        break;
      }
      case ACTION_START_GAME:
      {
        m_game_mode.reset(new GameSession());
        break;
      }
    }
  }

  m_scheduled_actions.clear();
}
