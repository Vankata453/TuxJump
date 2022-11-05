#ifndef TUXJUMP_GAME_SESSION_HEADER
#define TUXJUMP_GAME_SESSION_HEADER

#include "video/render_context.hpp"
#include "game/player.hpp"

class GameSession final
{
private:
  std::unique_ptr<Player> m_player;

public:
  GameSession();
  ~GameSession();

  void draw(RenderContext& context);
  void process_event(SDL_Event& ev);

private:
  GameSession(const GameSession&) = delete;
  GameSession& operator=(const GameSession&) = delete;
};

#endif
