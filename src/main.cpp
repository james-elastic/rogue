// Including core SDL libraries
#include <SDL2/SDL.h> // if used required -lSDL2 to the LDFLAGS
#include <SDL2/SDL_image.h> // if used requires -lSDL2_image to the LDFLAGS
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>

// Including basic CPP libraries
#include <stdio.h>
#include <string>

#include "util.h"
#include "error.h"
#include "texture.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int SCOREBOARD_WIDTH = SCREEN_WIDTH;
const int SCOREBOARD_HEIGHT = 20;

const int GAME_BORDER = 10; // 10px border
const int GAME_WIDTH = SCREEN_WIDTH - GAME_BORDER;
const int GAME_HEIGHT = SCREEN_HEIGHT - SCOREBOARD_HEIGHT - GAME_BORDER;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to the snake
LTexture gSnakeSurfaces[ SNAKE_SURFACE_TOTAL ];

//Current displayed image
LTexture gCurrentTexture;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    handle_error( INIT_SDL_INIT, SDL_GetError() );
    return false;
  }

  //Create window
  gWindow = SDL_CreateWindow( "|3 => Snake",
			      SDL_WINDOWPOS_UNDEFINED,
			      SDL_WINDOWPOS_UNDEFINED,
			      SCREEN_WIDTH,
			      SCREEN_HEIGHT,
			      SDL_WINDOW_SHOWN );
  if( gWindow == NULL ) {
    handle_error( INIT_SDL_CREATE_WINDOW, SDL_GetError() );
    return false;
  }

  //Create renderer for window
  gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
  if( gRenderer == NULL ) {
    handle_error( INIT_SDL_CREATE_RENDERER, SDL_GetError() );
    return false;
  }

  //Initialize renderer color
  SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

  //Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
    handle_error( INIT_IMG_INIT, IMG_GetError() );
    return false;
  }

  //Instantiate classes for each sprite map we need
  //for(int i = 0; i < SNAKE_SURFACE_TOTAL; ++i) {
  //  gSnakeSurfaces[i] = LTexture();
  //}

  return true;
}

bool loadMedia()
{
  gSnakeSurfaces[ SNAKE_SURFACE_HEAD ].loadFromFile( gRenderer, "img/head.png" );
  /*if( gSnakeSurfaces[ SNAKE_SURFACE_HEAD ] == NULL ) {
    handle_error( LOADMEDIA_LOAD_TEXTURE, "img/head.png" );
    return false;
    }*/

  gSnakeSurfaces[ SNAKE_SURFACE_BODY ].loadFromFile( gRenderer, "img/scale.png" );
  /*if( gSnakeSurfaces[ SNAKE_SURFACE_BODY ] == NULL ) {
    handle_error( LOADMEDIA_LOAD_TEXTURE, "img/scale.png" );
    return false;
    }*/

  gSnakeSurfaces[ SNAKE_SURFACE_TAIL ].loadFromFile( gRenderer, "img/tail.png" );
  /*if( gSnakeSurfaces[ SNAKE_SURFACE_TAIL ] == NULL ) {
    handle_error( LOADMEDIA_LOAD_TEXTURE, "img/tail.png" );
    return false;
    }*/

  return true;
}

void close()
{
  //Free loaded images
  for(int i = 0; i < SNAKE_SURFACE_TOTAL; ++i) {
    gSnakeSurfaces[i].free();
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
  if( !init() ) {
    handle_error( MAIN_INIT, NULL );
    return MAIN_INIT;
  }

  //Load media
  if( !loadMedia() ) {
    handle_error ( MAIN_LOAD_MEDIA, NULL );
    return MAIN_LOAD_MEDIA;
  }

  //Main loop flag
  bool quit = false;

  //Event handler
  SDL_Event e;

  // Setup the two viewports
  SDL_Rect vp_scoreboard;
  SDL_Rect vp_game;

  vp_scoreboard.x = 0;
  vp_scoreboard.y = 0;
  vp_scoreboard.w = SCOREBOARD_WIDTH;
  vp_scoreboard.h = SCOREBOARD_HEIGHT;

  vp_game.x = 0 + (GAME_BORDER / 2);
  vp_game.y = SCOREBOARD_HEIGHT + (GAME_BORDER / 2);
  vp_game.w = GAME_WIDTH;
  vp_game.h = GAME_HEIGHT;
      
  //Set default current surface
  gCurrentTexture = gSnakeSurfaces[ SNAKE_SURFACE_HEAD ];
	    
  //While application is running
  while( !quit ) {
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 ) {
      //User requests quit
      if( e.type == SDL_QUIT ) {
	quit = true;
      }
      //User presses a key
      else if( e.type == SDL_KEYDOWN ) {
	//Select surfaces based on key press
	switch( e.key.keysym.sym ) {
	  /*
	    case SDLK_UP:
	    gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
	    break;

	    case SDLK_DOWN:
	    gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
	    break;
	  */
	case SDLK_LEFT:
	  gCurrentTexture = gSnakeSurfaces[ SNAKE_SURFACE_HEAD ];
	  break;

	case SDLK_RIGHT:
	  gCurrentTexture = gSnakeSurfaces[ SNAKE_SURFACE_TAIL ];
	  break;

	default:
	  gCurrentTexture = gSnakeSurfaces[ SNAKE_SURFACE_BODY ];
	  break;
	}
      }
    }

    //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
    //Clear screen
    SDL_RenderClear( gRenderer );

    SDL_RenderSetViewport( gRenderer, &vp_scoreboard );
    //Render texture to screen
    //SDL_RenderCopy( gRenderer, gCurrentTexture, NULL, NULL );
    gCurrentTexture.render( gRenderer, 0, 0 );
    
    SDL_RenderSetViewport( gRenderer, &vp_game );
    //SDL_RenderCopy( gRenderer, gCurrentTexture, NULL, NULL );
    gCurrentTexture.render( gRenderer, 0, 0 );
    
    //Update screen
    SDL_RenderPresent( gRenderer );
  }
  
  //Free resources and close SDL
  close();
  
  return 0;
}
