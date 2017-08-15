#include <stdio.h>
#include "error.h"

int handle_error( int errno, const char* err_msg ) {
  switch( errno ) {
  case INIT_SDL_INIT:
    printf( "SDL could not initialize! SDL Error: %s\n", err_msg );
    break;
  case INIT_SDL_CREATE_WINDOW:
    printf( "Window could not be created! SDL Error: %s\n", err_msg );
    break;
  case INIT_SDL_CREATE_RENDERER:
    printf( "Renderer could not be created! SDL Error: %s\n", err_msg );
    break;
  case INIT_IMG_INIT:
    printf( "SDL_image could not initialize! SDL_image Error: %s\n", err_msg );
    break;
  }
}
