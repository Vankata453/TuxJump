#include "render_context.hpp"

#include "game/manager.hpp"
#include "game/global.hpp"
#include "game/resources.hpp"
#include "util/log.hpp"

RenderContext::RenderContext(SDL_Window* window) :
  m_renderer(nullptr),
  m_texture_manager(),
  m_width(SCREEN_WIDTH),
  m_height(SCREEN_HEIGHT)
{
  // Create renderer
  m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (m_renderer == NULL)
    log_fatal("Renderer could not be created! SDL Error: %s\n", SDL_GetError());

  m_texture_manager = std::make_unique<TextureManager>(m_renderer);
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

// Draw textures

void
RenderContext::draw_image(std::string path, int x, int y, int w, int h)
{
  SDL_Rect render_rect = { x, y, w, h };
  SDL_RenderCopy(m_renderer, m_texture_manager->load_image(path), NULL, &render_rect);
}

Rect
RenderContext::draw_text(TTF_Font* font, std::string text, int x, int y, Alignment alignment, Color& color)
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

  SDL_Rect render_rect = { x, y, texture.size.w, texture.size.h };
  SDL_RenderCopy(m_renderer, texture.texture, NULL, &render_rect);

  return { x, y, texture.size.w, texture.size.h }; // Return position and size of text surface
}

void
RenderContext::draw_rect(int x, int y, int w, int h, Color& color)
{
  SDL_Rect render_rect = { x, y, w, h };
  SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 1); // Temporarily set render draw color
  SDL_RenderDrawRect(m_renderer, &render_rect);

  reset_color();
}

void
RenderContext::draw_filled_rect(int x, int y, int w, int h, Color& color)
{
  SDL_Rect render_rect = { x, y, w, h };
  SDL_RenderCopy(m_renderer, m_texture_manager->load_filled_rect({ w, h }, color), NULL, &render_rect);
}

void
RenderContext::draw_line(int x1, int y1, int x2, int y2, Color& color)
{
  SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 1); // Temporarily set render draw color
  SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);

  reset_color();
}

// Get dynamic texture properties (without drawing)

Size
RenderContext::get_text_size(TTF_Font* font, std::string text)
{
  return m_texture_manager->load_text(font, text, Resources::Colors::WHITE).size; // Return size of text surface
}
