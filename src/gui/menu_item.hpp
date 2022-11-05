#ifndef TUXJUMP_GUI_MENU_ITEM_HEADER
#define TUXJUMP_GUI_MENU_ITEM_HEADER

#include <SDL2/SDL.h>

#include <memory>
#include <functional>
#include <string>

#include "video/render_context.hpp"

class MenuItem final
{
private:
  std::string m_text;
  std::function<void ()> m_callback;

public:
  MenuItem(const std::string text, const std::function<void ()>& callback = [](){});
  ~MenuItem();

  void draw(RenderContext& context, int x, int y, bool selected);
  void process_event(SDL_Event& ev);

  // Set properties
  void set_text(const std::string text) { m_text = text; }
  void set_callback(const std::function<void ()>& callback) { m_callback = callback; }

private:
  MenuItem(const MenuItem&) = delete;
  MenuItem& operator=(const MenuItem&) = delete;
};

#endif
