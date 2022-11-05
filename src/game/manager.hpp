// The GameManager is the root to the management of main game events.
// EXAMPLES: Drawing content on screen and processing events.
// GameManager also stores important variables and instances for the game to function.

#ifndef TUXJUMP_GAME_MANAGER_HEADER
#define TUXJUMP_GAME_MANAGER_HEADER

#include <memory>

#include "video/render_context.hpp"
#include "game/session.hpp"
#include "gui/menu_manager.hpp"

class GameManager final
{
private:
  static GameManager* s_instance;

public:
  static GameManager& instance();

  // Store important to the game variables and instances
  std::unique_ptr<MenuManager> m_menu_manager;
  std::unique_ptr<GameSession> m_game_session;

private:
  enum GameMode
  {
    MODE_MENU,
    MODE_GAME
  };

  GameMode m_mode;
  bool m_quit; // Requested game quit

public:
  GameManager();
  ~GameManager();

  void draw(RenderContext& context);
  void process_event(SDL_Event& ev);

  // Game mode management
  void start_game();
  void exit_game();
  void quit_game();

  // Get properties
  bool quit_requested() const { return m_quit; }

private:
  GameManager(const GameManager&) = delete;
  GameManager& operator=(const GameManager&) = delete;
};

#endif
