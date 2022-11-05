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

public:
  RenderContext(SDL_Window* window);
  ~RenderContext();

  // Renderer functions (SDL)
  void render_clear();
  void render_present();

  // General functions
  void reset_color();

  // Draw textures
  void draw_image(std::string path, int x, int y, int w, int h);
  Rect draw_text(TTF_Font* font, std::string text, int x, int y, Alignment alignment, Color& color);
  void draw_rect(int x, int y, int w, int h, Color& color);
  void draw_filled_rect(int x, int y, int w, int h, Color& color);
  void draw_line(int x1, int y1, int x2, int y2, Color& color);

  // Get dynamic texture properties (without drawing)
  Size get_text_size(TTF_Font* font, std::string text);

  // Get properties
  int get_width() const { return m_width; }
  int get_height() const { return m_height; }
  Size get_size() const { return Size(m_width, m_height); }

private:
  RenderContext(const RenderContext&) = delete;
  RenderContext& operator=(const RenderContext&) = delete;
};

#endif
 
