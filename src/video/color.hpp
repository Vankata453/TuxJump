#ifndef TUXJUMP_VIDEO_COLOR_HEADER
#define TUXJUMP_VIDEO_COLOR_HEADER

#include <SDL2/SDL.h>

#include <string>

class Color : public SDL_Color
{
public:
  std::string to_string() const { return std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b); }
};

#endif
