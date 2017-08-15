enum error_codes {
  INIT_SDL_INIT,
  INIT_SDL_CREATE_WINDOW,
  INIT_SDL_CREATE_RENDERER,
  INIT_SDL_SET_RENDERER_DRAW_COLOR,
  INIT_IMG_INIT
};

int handle_error( int errno, const char* err_msg );
