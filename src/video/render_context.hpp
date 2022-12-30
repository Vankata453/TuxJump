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

#ifndef TUXJUMP_VIDEO_RENDER_CONTEXT_HEADER
#define TUXJUMP_VIDEO_RENDER_CONTEXT_HEADER

#include <memory>

#include "video/texture_manager.hpp"

// A class to allow rendering textures and shapes on screen.
class RenderContext final
{
private:
  SDL_Renderer* m_renderer;
  std::unique_ptr<TextureManager> m_texture_manager;

public:
  RenderContext(SDL_Window* window);
  ~RenderContext();

  // Renderer functions (SDL)
  void render_clear();
  void render_present();

  // General functions
  void reset_color() const;
  SDL_FRect create_rect(const float& x, const float& y, const float& w, const float& h) const;

  // Draw textures
  void draw_texture(SDL_Texture* texture, const float& x, const float& y,
                    const float& w, const float& h, const float& alpha = 255) const;
  void draw_texture(SDL_Texture* texture, const Rectf& rect, const float& alpha = 255) const;

  SDL_Texture* draw_image(const std::string& path, const float& x, const float& y, const float& w, const float& h) const;
  SDL_Texture* draw_image(const std::string& path, const Rectf& rect) const;

  Rectf draw_text(TTF_Font* font, const std::string& text, float x, const float& y,
                  const Alignment& alignment, const Color& color) const;

  void draw_rect(const float& x, const float& y, const float& w, const float& h, const Color& color) const;
  void draw_rect(const Rectf& rect, const Color& color) const;

  void draw_filled_rect(const float& x, const float& y, const float& w, const float& h, const Color& color) const;
  void draw_filled_rect(const Rectf& rect, const Color& color) const;

  void draw_line(const float& x1, const float& y1, const float& x2, const float& y2, const Color& color) const;

  // Get dynamic texture properties (without drawing)
  Sizef get_text_size(TTF_Font* font, const std::string& text) const;

  // Get properties
  const int& get_width() const;
  const int& get_height() const;
  Size get_size() const { return Size(get_width(), get_height()); }

private:
  RenderContext(const RenderContext&) = delete;
  RenderContext& operator=(const RenderContext&) = delete;
};

#endif
