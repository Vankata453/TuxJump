#ifndef TUXJUMP_GUI_MENU_MANAGER_HEADER
#define TUXJUMP_GUI_MENU_MANAGER_HEADER

#include <memory>
#include <vector>

#include "video/render_context.hpp"
#include "gui/menu_factory.hpp"

class MenuManager final
{
public:
  static MenuManager& instance();

private:
  std::vector<std::unique_ptr<Menu>> m_menu_stack;

public:
  MenuManager();
  ~MenuManager();

  void draw(RenderContext& context);
  void process_event(SDL_Event& event);

  // Menu management
  void push_menu(std::unique_ptr<Menu> menu);
  void push_menu(MenuType type);
  void pop_menu();
  void clear_menu_stack();

  // Get dynamic properties
  bool is_active() { return !m_menu_stack.empty(); }
  Menu* current_menu() { return m_menu_stack.end()[-1].get(); }

private:
  MenuManager(const MenuManager&) = delete;
  MenuManager& operator=(const MenuManager&) = delete;
};

#endif

