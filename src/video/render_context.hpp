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
#include <string>

#include "video/texture_manager.hpp"

class RenderContext final
{
private:
  SDL_Renderer* m_renderer;
  std::unique_ptr<TextureManager> m_texture_manager;

  const int m_width;
  const int m_height;

  Positionf m_offset;

public:
  RenderContext(SDL_Window* window);
  ~RenderContext();

  // Renderer functions (SDL)
  void render_clear();
  void render_present();

  // General functions
  void reset_color();
  SDL_FRect create_rect(const float& x, const float& y, const float& w, const float& h) const;

  // Draw textures
  void draw_texture(SDL_Texture* texture, float x, float y, float w, float h);
  void draw_image(std::string path, float x, float y, float w, float h);
  Rectf draw_text(TTF_Font* font, std::string text, float x, float y, Alignment alignment, Color& color);
  void draw_rect(float x, float y, float w, float h, Color& color);
  void draw_filled_rect(float x, float y, float w, float h, Color& color);
  void draw_line(float x1, float y1, float x2, float y2, Color& color);

  // Get dynamic texture properties (without drawing)
  Sizef get_text_size(TTF_Font* font, std::string text);

  // Get properties
  const int& get_width() const { return m_width; }
  const int& get_height() const { return m_height; }
  Size get_size() const { return Size(m_width, m_height); }

  // Set properties
  void set_offset_x(const float& new_offset) { m_offset.x = new_offset; }
  void set_offset_y(const float& new_offset) { m_offset.y = new_offset; }
  void clear_offset_x() { m_offset.x = 0.0f; }
  void clear_offset_y() { m_offset.y = 0.0f; }

private:
  RenderContext(const RenderContext&) = delete;
  RenderContext& operator=(const RenderContext&) = delete;
};

#endif
