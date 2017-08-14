// Including core SDL libraries
#include <SDL2/SDL.h> // if used required -lSDL2 to the LDFLAGS
#include <SDL2/SDL_image.h> // if used requires -lSDL2_image to the LDFLAGS
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>

// Including basic CPP libraries
#include <stdio.h>
#include <string>

#include "util.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress
SDL_Texture* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Texture* gCurrentTexture = NULL;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
      printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
      success = false;
    }
  else
    {
      //Create window
      gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
      if( gWindow == NULL )
        {
	  printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	  success = false;
        }
      else
        {
	  //Create renderer for window
	  gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	  if( gRenderer == NULL )
            {
	      printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
	      success = false;
            }
	  else
            {
	      //Initialize renderer color
	      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

	      //Initialize PNG loading
	      int imgFlags = IMG_INIT_PNG;
	      if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
		  printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		  success = false;
                }
            }
        }
    }

  return success;
}

bool loadMedia()
{
  //Loading success flag
  bool success = true;

  //Load default surface
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadTexture( "img/press.bmp", gRenderer );
  if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
      printf( "Failed to load default image!\n" );
      success = false;
    }

  //Load up surface
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadTexture( "img/up.bmp", gRenderer );
  if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
      printf( "Failed to load up image!\n" );
      success = false;
    }

  //Load down surface
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadTexture( "img/down.bmp", gRenderer );
  if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
      printf( "Failed to load down image!\n" );
      success = false;
    }

  //Load left surface
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadTexture( "img/left.bmp", gRenderer );
  if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
      printf( "Failed to load left image!\n" );
      success = false;
    }

  //Load right surface
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadTexture( "img/right.bmp", gRenderer );
  if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
      printf( "Failed to load right image!\n" );
      success = false;
    }

  return success;
}

void close()
{
    //Free loaded images
  for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
    SDL_DestroyTexture( gKeyPressSurfaces[i] );
    gKeyPressSurfaces[i] = NULL;
  }

    //Destroy window    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
{
  //Start up SDL and create window
  if( !init() )
    {
      printf( "Failed to initialize!\n" );
    }
  else
    {
      //Load media
      if( !loadMedia() )
        {
	  printf( "Failed to load media!\n" );
        }
      else
        {
	  //Main loop flag
	  bool quit = false;

	  //Event handler
	  SDL_Event e;

	  //Set default current surface
	  gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
	    
	  //While application is running
	  while( !quit )
            {
	      //Handle events on queue
	      while( SDL_PollEvent( &e ) != 0 )
                {
		  //User requests quit
		  if( e.type == SDL_QUIT )
                    {
		      quit = true;
                    }
		  //User presses a key
		  else if( e.type == SDL_KEYDOWN )
                    {
		      //Select surfaces based on key press
		      switch( e.key.keysym.sym )
                        {
			case SDLK_UP:
			  gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
			  break;

			case SDLK_DOWN:
			  gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
			  break;

			case SDLK_LEFT:
			  gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
			  break;

			case SDLK_RIGHT:
			  gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
			  break;

			default:
			  gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
			  break;
                        }
                    }
                }

	      //Clear screen
                SDL_RenderClear( gRenderer );

                //Render texture to screen
                SDL_RenderCopy( gRenderer, gCurrentTexture, NULL, NULL );

                //Update screen
                SDL_RenderPresent( gRenderer );
	    }
        }
    }

  //Free resources and close SDL
  close();

  return 0;
}
