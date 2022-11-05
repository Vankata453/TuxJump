#ifndef TUXJUMP_VIDEO_TEXT_HEADER
#define TUXJUMP_VIDEO_TEXT_HEADER

#include <SDL2/SDL.h>

#include "video/rect.hpp"

struct Text
{
  SDL_Texture* texture;
  Size size;
};

enum Alignment
{
  ALIGN_LEFT,
  ALIGN_CENTER,
  ALIGN_RIGHT
};

#endif
