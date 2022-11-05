#include "gui/menu_factory.hpp"

#include "game/manager.hpp"
#include "gui/menu_manager.hpp"

// Create a specified menu
std::unique_ptr<Menu>
MenuFactory::create(MenuType type)
{
  auto menu = std::make_unique<Menu>();
  switch (type)
  {
    case MAIN_MENU:
    {
      menu->add_item("Start Game", []() { GameManager::instance().start_game(); });
      menu->add_item("Options", []() { MenuManager::instance().push_menu(OPTIONS_MENU); });
      menu->add_item("Quit", []() { GameManager::instance().quit_game(); });
      break;
    }
    case OPTIONS_MENU:
    {
      // TODO
      break;
    }
  }
  return std::move(menu);
}
