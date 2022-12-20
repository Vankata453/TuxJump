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
  m_texture_manager()
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
  reset_color();
  SDL_RenderClear(m_renderer);
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
  return { x, y, w, h };
}

// Draw textures

void
RenderContext::draw_texture(SDL_Texture* texture, const float& x, const float& y, const float& w, const float& h)
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
RenderContext::draw_image(const std::string& path, const float& x, const float& y, const float& w, const float& h)
{
  SDL_Texture* texture = m_texture_manager->load_image(path);
  draw_texture(texture, x, y, w, h);
  return texture;
}

SDL_Texture*
RenderContext::draw_image(const std::string& path, const Rectf& rect)
{
  return draw_image(path, rect.x, rect.y, rect.w, rect.h);
}

Rectf
RenderContext::draw_text(TTF_Font* font, const std::string& text, float x, const float& y,
                         const Alignment& alignment, const Color& color)
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
RenderContext::draw_rect(const float& x, const float& y, const float& w, const float& h, const Color& color)
{
  SDL_FRect render_rect = create_rect(x, y, w, h);
  SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a); // Temporarily set render draw color
  SDL_RenderDrawRectF(m_renderer, &render_rect);

  reset_color();
}

void
RenderContext::draw_rect(const Rectf& rect, const Color& color)
{
  draw_rect(rect.x, rect.y, rect.w, rect.h, color);
}

void
RenderContext::draw_filled_rect(const float& x, const float& y, const float& w, const float& h, const Color& color)
{
  SDL_FRect render_rect = create_rect(x, y, w, h);
  SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a); // Temporarily set render draw color
  SDL_RenderFillRectF(m_renderer, &render_rect);

  reset_color();
}

void
RenderContext::draw_filled_rect(const Rectf& rect, const Color& color)
{
  draw_filled_rect(rect.x, rect.y, rect.w, rect.h, color);
}

void
RenderContext::draw_line(const float& x1, const float& y1, const float& x2, const float& y2, const Color& color)
{
  SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a); // Temporarily set render draw color
  SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);

  reset_color();
}

// Get dynamic texture properties (without drawing)

Sizef
RenderContext::get_text_size(TTF_Font* font, const std::string& text)
{
  return m_texture_manager->load_text(font, text, Resources::Colors::WHITE).size; // Return size of text surface
}

// Get properties

const int&
RenderContext::get_width() const
{
  return SCREEN_WIDTH;
}

const int&
RenderContext::get_height() const
{
  return SCREEN_HEIGHT;
}
