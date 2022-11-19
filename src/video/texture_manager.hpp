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

#ifndef TUXJUMP_VIDEO_TEXTURE_MANAGER_HEADER
#define TUXJUMP_VIDEO_TEXTURE_MANAGER_HEADER

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <map>
#include <string>

#include "video/color.hpp"
#include "video/text.hpp"

class TextureManager final
{
private:
  SDL_Renderer* m_renderer;

  std::map<std::string, SDL_Texture*> m_image_textures;
  std::map<std::string, Text> m_text_textures;
  std::map<std::string, SDL_Texture*> m_rect_textures;

public:
  TextureManager(SDL_Renderer* renderer);
  ~TextureManager();

  // Load textures
  SDL_Texture* load_image(std::string& path);
  const Text& load_text(TTF_Font* font, std::string& text, Color& color);
  SDL_Texture* load_filled_rect(Sizef size, Color& color);

private:
  TextureManager(const TextureManager&) = delete;
  TextureManager& operator=(const TextureManager&) = delete;
};

#endif
