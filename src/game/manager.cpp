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

#include "game/manager.hpp"

#include <iostream>

#include "game/resources.hpp"
#include "gui/menu_manager.hpp"

GameManager::GameManager() :
  // Define important to the game variables and instances
  m_menu_manager(std::make_unique<MenuManager>()),
  m_game_session(nullptr),
  m_mode(MODE_MENU),
  m_start_game(false),
  m_exit_game(false),
  m_quit(false)
{
  m_menu_manager->push_menu(MenuType::MAIN_MENU); // Show the main menu
}

GameManager::~GameManager()
{
}

void
GameManager::draw(RenderContext& context)
{
  try
  {
    switch (m_mode)
    {
      case MODE_MENU:
      {
        m_menu_manager->draw(context);
        break;
      }
      case MODE_GAME:
      {
        m_game_session->draw(context);
        break;
      }
    }
  }
  catch (std::exception& err)
  {
    // Catch fatal errors
    std::cout << err.what() << std::endl;
    quit_game();
  }

  update();
}

void
GameManager::process_event(SDL_Event& ev)
{
  try
  {
    switch (m_mode)
    {
      case MODE_MENU:
      {
        m_menu_manager->process_event(ev);
        break;
      }
      case MODE_GAME:
      {
        m_game_session->process_event(ev);
        break;
      }
    }
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
  if (m_exit_game)
  {
    m_mode = MODE_MENU;
    m_game_session.reset();
    m_exit_game = false;
  }
  else if (m_start_game)
  {
    m_game_session.reset(new GameSession());
    m_mode = MODE_GAME;
    m_start_game = false;
  }
}
