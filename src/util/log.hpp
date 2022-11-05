#include "game/manager.hpp"

template<typename... Args>
void log_fatal(Args&&... args)
{
  printf(std::forward<Args>(args)...);
  GameManager::instance().quit_game();
}
