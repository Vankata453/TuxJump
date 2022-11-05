#ifndef TUXJUMP_GAME_PLAYER_HEADER
#define TUXJUMP_GAME_PLAYER_HEADER

#include "video/render_context.hpp"

class Player final
{
private:
  static const float s_max_jump_height;
  static const float s_jump_speed;

private:
  float m_jump_height;
  bool m_stop_jump;

public:
  Player();
  ~Player();

  void draw(RenderContext& context);
  void update();
  void process_event(SDL_Event& ev);

private:
  // Player physics
  void jump();
  void update_jump();

private:
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
};

#endif
