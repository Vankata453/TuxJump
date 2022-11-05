#ifndef TUXJUMP_GAME_RESOURCES_HEADER
#define TUXJUMP_GAME_RESOURCES_HEADER

#include <SDL2/SDL_ttf.h>

#include "video/color.hpp"
#include "video/render_context.hpp"

namespace Resources
{
  namespace Fonts
  {
    extern TTF_Font* DEFAULT;

    void init_fonts();
    void close_fonts();
  }

  namespace Colors
  {
    extern Color BLACK;
    extern Color WHITE;
  }
}

#endif
