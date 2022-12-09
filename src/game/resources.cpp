//  TuxJump
//  Copyright (C) 2022 Vankata453
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "game/resources.hpp"

#include "util/file_system.hpp"
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
        Log::fatal("Couldn't initialize SDL2_TTF: ", TTF_GetError());
      }

      // Initialize fonts
      DEFAULT = TTF_OpenFont(FileSystem::create_path("data/fonts/Roboto-Regular.ttf").c_str(), 24); // Load the default font
      if (DEFAULT == NULL)
      {
        Log::fatal("Couldn't load default TTF font: ", TTF_GetError()); // Log font loading error
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
    Color YELLOW = { 255, 255, 0 };
  }
}
