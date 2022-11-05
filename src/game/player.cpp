#include "game/player.hpp"

#include "game/global.hpp"
#include "game/resources.hpp"

const float Player::s_max_jump_height = 100.0f;
const float Player::s_jump_speed = 0.15f;

Player::Player() :
  m_jump_height(0.0f),
  m_stop_jump(false)
{
}

Player::~Player()
{
}

void
Player::draw(RenderContext& context)
{
  context.draw_image("data/images/tux.png", context.get_width() * 0.15,
                      context.get_height() * 0.7 - m_jump_height, 40, 40);
}

void
Player::update()
{
  update_jump();
}

void
Player::process_event(SDL_Event& ev)
{
  switch (ev.type)
  {
    case SDL_KEYDOWN:
    {
      switch (ev.key.keysym.sym)
      {
        case SDLK_SPACE:
        case SDLK_UP:
          jump();
          break;
      }
    }
  }
}

// Player physics

void
Player::jump()
{
  if (m_jump_height > 0.0f) return;

  m_stop_jump = false;
  m_jump_height += s_jump_speed;
}

void
Player::update_jump()
{
  if (m_jump_height <= 0.0f) return;

  if (m_jump_height >= s_max_jump_height) m_stop_jump = true;
  m_jump_height += s_jump_speed * (m_stop_jump ? -1.0f : 1.0f);
}
