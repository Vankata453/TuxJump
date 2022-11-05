#include "game/session.hpp"

GameSession::GameSession() :
  m_player(std::make_unique<Player>())
{
}

GameSession::~GameSession()
{
}

void
GameSession::draw(RenderContext& context)
{
  m_player->update();
  m_player->draw(context);
}

void
GameSession::process_event(SDL_Event& ev)
{
  m_player->process_event(ev);
}
