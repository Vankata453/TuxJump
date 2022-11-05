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
  Text load_text(TTF_Font* font, std::string& text, Color& color);
  SDL_Texture* load_filled_rect(Size size, Color& color);

private:
  TextureManager(const TextureManager&) = delete;
  TextureManager& operator=(const TextureManager&) = delete;
};

#endif
