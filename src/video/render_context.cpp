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

#include "render_context.hpp"

#include "game/manager.hpp"
#include "game/global.hpp"
#include "game/resources.hpp"
#include "util/log.hpp"

RenderContext::RenderContext(SDL_Window* window) :
  m_renderer(nullptr),
  m_texture_manager(),
  m_width(SCREEN_WIDTH),
  m_height(SCREEN_HEIGHT),
  m_offset(0.0f, 0.0f)
{
  // Create renderer
  m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (m_renderer == NULL)
    Log::fatal("Renderer could not be created! SDL Error: ", SDL_GetError());

  m_texture_manager.reset(new TextureManager(m_renderer));
}

RenderContext::~RenderContext()
{
  // Destroy texture manager
  m_texture_manager.reset();

  // Destroy renderer
  SDL_DestroyRenderer(m_renderer);
}

// Renderer functions (SDL)

void
RenderContext::render_clear()
{
  SDL_RenderClear(m_renderer);
  reset_color();
}

void
RenderContext::render_present()
{
  SDL_RenderPresent(m_renderer);
}

// General functions

void
RenderContext::reset_color()
{
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 1);
}

SDL_FRect
RenderContext::create_rect(const float& x, const float& y, const float& w, const float& h) const
{
  return { x - m_offset.x, y - m_offset.y, w, h };
}

// Draw textures

void
RenderContext::draw_texture(SDL_Texture* texture, float x, float y, float w, float h)
{
  SDL_FRect render_rect = create_rect(x, y, w, h);
  SDL_RenderCopyF(m_renderer, texture, NULL, &render_rect);
}

void
RenderContext::draw_texture(SDL_Texture* texture, const Rectf& rect)
{
  draw_texture(texture, rect.x, rect.y, rect.w, rect.h);
}

SDL_Texture*
RenderContext::draw_image(std::string path, float x, float y, float w, float h)
{
  SDL_Texture* texture = m_texture_manager->load_image(path);
  draw_texture(texture, x, y, w, h);
  return texture;
}

SDL_Texture*
RenderContext::draw_image(std::string path, const Rectf& rect)
{
  return draw_image(std::move(path), rect.x, rect.y, rect.w, rect.h);
}

Rectf
RenderContext::draw_text(TTF_Font* font, std::string text, float x, float y, Alignment alignment, Color& color)
{
  const auto texture = m_texture_manager->load_text(font, text, color);

  // Modify position of text, according to chosen alignment (LEFT alignment does not modify anything; not included)
  switch (alignment)
  {
    case ALIGN_CENTER:
      x -= texture.size.w / 2;
      break;
    case ALIGN_RIGHT:
      x -= texture.size.w;
      break;
  }

  draw_texture(texture.texture, x, y, texture.size.w, texture.size.h);

  return { x, y, texture.size.w, texture.size.h }; // Return position and size of text surface
}

void
RenderContext::draw_rect(float x, float y, float w, float h, Color& color)
{
  SDL_FRect render_rect = create_rect(x, y, w, h);
  SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 1); // Temporarily set render draw color
  SDL_RenderDrawRectF(m_renderer, &render_rect);

  reset_color();
}

void
RenderContext::draw_rect(const Rectf& rect, Color& color)
{
  draw_rect(rect.x, rect.y, rect.w, rect.h, color);
}

void
RenderContext::draw_filled_rect(float x, float y, float w, float h, Color& color)
{
  draw_texture(m_texture_manager->load_filled_rect({ w, h }, color), x, y, w, h);
}

void
RenderContext::draw_filled_rect(const Rectf& rect, Color& color)
{
  draw_filled_rect(rect.x, rect.y, rect.w, rect.h, color);
}

void
RenderContext::draw_line(float x1, float y1, float x2, float y2, Color& color)
{
  SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 1); // Temporarily set render draw color
  SDL_RenderDrawLine(m_renderer, x1 - m_offset.x, y1 - m_offset.y, x2 - m_offset.x, y2 - m_offset.y);

  reset_color();
}

// Get dynamic texture properties (without drawing)

Sizef
RenderContext::get_text_size(TTF_Font* font, std::string text)
{
  return m_texture_manager->load_text(font, text, Resources::Colors::WHITE).size; // Return size of text surface
}
