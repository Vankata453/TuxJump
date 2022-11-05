#ifndef TUXJUMP_GUI_MENU_FACTORY_HEADER
#define TUXJUMP_GUI_MENU_FACTORY_HEADER

#include <memory>

#include "gui/menu.hpp"

enum MenuType
{
  MAIN_MENU,
  OPTIONS_MENU
};

class MenuFactory final
{
public:
  static std::unique_ptr<Menu> create(MenuType type);

private:
  MenuFactory(const MenuFactory&) = delete;
  MenuFactory& operator=(const MenuFactory&) = delete;
};

#endif
