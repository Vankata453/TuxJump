#include <SDL2/SDL.h>

#include <string>

#include "video/render_context.hpp"
#include "game/manager.hpp"
#include "game/global.hpp"
#include "game/resources.hpp"

int main(int argc, char* args[])
{
  SDL_Window* window = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
    const std::string window_title = GAME_TITLE + (GAME_DEV_BUILD ? " [DEVELOPMENT BUILD]" : "");
		window = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
      GameManager game_manager; // Define an instance of the game manager
      RenderContext context(window); // Create a rendering context (including renderer)
      SDL_Event ev; // Create an event handler

      Resources::Fonts::init_fonts(); // Initialize fonts as resources

      // Main game loop
      while (!game_manager.quit_requested())
      {
        if (SDL_PollEvent(&ev) != 0)
        {
          if (ev.type == SDL_QUIT) // Quit registered by SDL
          {
            game_manager.quit_game();
          }
          else
          {
            game_manager.process_event(ev);
          }
        }

        context.render_clear();
        game_manager.draw(context);
        context.render_present();
      }
		}
	}

  Resources::Fonts::close_fonts(); // Close all fonts
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
