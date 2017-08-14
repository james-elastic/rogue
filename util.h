// Including core SDL libraries
#include <SDL2/SDL.h> // if used required -lSDL2 to the LDFLAGS
#include <SDL2/SDL_image.h> // if used requires -lSDL2_image to the LDFLAGS
#include <string>

//Key press surfaces constants
enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

//Loads individual image
SDL_Texture* loadTexture( std::string path, SDL_Renderer* gRenderer );
SDL_Surface* loadSurface( std::string path, SDL_Surface* gScreenSurface );
