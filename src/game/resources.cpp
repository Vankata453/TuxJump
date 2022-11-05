#include "game/resources.hpp"

#include "util/log.hpp"

namespace Resources
{
  // Fonts
  namespace Fonts
  {
    TTF_Font* DEFAULT = NULL;

    void init_fonts()
    {
      // Initialize TTF
      if (TTF_Init() < 0)
      {
        log_fatal("Couldn't initialize SDL2_TTF: %s\n", TTF_GetError());
      }

      // Initialize fonts
      DEFAULT = TTF_OpenFont("../data/fonts/Roboto-Regular.ttf", 24); // Load the default font
      if (DEFAULT == NULL)
      {
        log_fatal("Couldn't load default TTF font: %s\n", TTF_GetError()); // Log font loading error
      }
    }

    void close_fonts()
    {
      // Close fonts
      TTF_CloseFont(DEFAULT);

      // Quit TTF
      TTF_Quit();
    }
  }

  // Colors
  namespace Colors
  {
    // Define various colors by RGB
    Color BLACK = { 0, 0, 0 };
    Color WHITE = { 255, 255, 255 };
  }
}
