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

#include "video/texture_manager.hpp"

#include "util/log.hpp"

TextureManager::TextureManager(SDL_Renderer* renderer) :
  m_renderer(renderer),
  m_image_textures(),
  m_text_textures(),
  m_rect_textures()
{
}

TextureManager::~TextureManager()
{
  // Destroy textures
  for (auto& texture_data : m_image_textures)
    SDL_DestroyTexture(texture_data.second);

  for (auto& texture_data : m_text_textures)
    SDL_DestroyTexture(texture_data.second.texture);

  for (auto& texture_data : m_rect_textures)
    SDL_DestroyTexture(texture_data.second);
}

// Load textures

SDL_Texture*
TextureManager::load_image(const std::string& path)
{
  if (m_image_textures.find(path) != m_image_textures.end())
    return m_image_textures[path]; // Texture exists


  SDL_Surface* surface = IMG_Load(("../" + path).c_str());
  if (!surface)
  {
    Log::fatal("Couldn't load image as surface: ", SDL_GetError());
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
  SDL_FreeSurface(surface);

  m_image_textures.insert({ path, texture }); // Cache texture
  return texture;
}

const Text&
TextureManager::load_text(TTF_Font* font, const std::string& text, const Color& color)
{
  if (m_text_textures.find(text) != m_text_textures.end())
    return m_text_textures[text]; // Texture exists


  SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
  if (text_surface == NULL)
  {
    Log::fatal("Couldn't render text surface: ", TTF_GetError());
  }
  SDL_Texture* text_texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);
  if (text_texture == NULL)
  {
    Log::fatal("Couldn't create texture from text surface: ", TTF_GetError());
  }
  SDL_FreeSurface(text_surface);

  Sizef text_size(static_cast<float>(text_surface->w), static_cast<float>(text_surface->h));
  m_text_textures.insert({ text, { text_texture, text_size } }); // Cache texture
  return m_text_textures[text];
}

SDL_Texture*
TextureManager::load_filled_rect(Sizef size, const Color& color)
{
  const std::string key = size.to_string() + " " + color.to_string();
  if (m_rect_textures.find(key) != m_rect_textures.end())
    return m_rect_textures[key]; // Texture exists


  SDL_Surface* color_surface = SDL_CreateRGBSurface(0, size.w, size.h, 1, color.r, color.g, color.b, 1);
  if (color_surface == NULL)
  {
    Log::fatal("Couldn't render color surface: ", TTF_GetError());
  }
  SDL_Texture* color_texture = SDL_CreateTextureFromSurface(m_renderer, color_surface);
  if (color_texture == NULL)
  {
    Log::fatal("Couldn't create texture from color surface: ", TTF_GetError());
  }
  SDL_FreeSurface(color_surface);

  m_rect_textures.insert({ key, color_texture }); // Cache texture
  return color_texture;
}

// Texture utilities

Size
TextureManager::get_size(SDL_Texture* texture)
{
  Size size;
  SDL_QueryTexture(texture, NULL, NULL, &size.w, &size.h);
  return size;
}

Sizef
TextureManager::get_sizef(SDL_Texture* texture)
{
  Size size = get_size(texture);
  return { static_cast<float>(size.w), static_cast<float>(size.h) };
}
