#include "gui/menu_item.hpp"

#include "game/resources.hpp"

MenuItem::MenuItem(const std::string text, const std::function<void ()>& callback) :
  m_text(text),
  m_callback(callback)
{
}

MenuItem::~MenuItem()
{
}

void
MenuItem::draw(RenderContext& context, int x, int y, bool selected)
{
  const auto text_rect = context.draw_text(Resources::Fonts::DEFAULT, m_text, x, y,
                                           ALIGN_CENTER, Resources::Colors::WHITE);
  if (selected) context.draw_line(text_rect.x, text_rect.y + text_rect.h, text_rect.x + text_rect.w, text_rect.y + text_rect.h,
                                  Resources::Colors::WHITE);
}

void
MenuItem::process_event(SDL_Event& ev)
{
  switch (ev.type)
  {
    case SDL_KEYDOWN:
    {
      if (ev.key.keysym.sym == SDLK_RETURN) m_callback(); // On "Enter" press, execute callback
      break;
    }
  }
}
