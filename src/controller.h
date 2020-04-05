#include <SDL2/SDL.h>

class JoyCon {
public:
  JoyCon();
  JoyCon(int maxJoyConsAllowed);
  
  ~JoyCon();

  /* takes an SDL_ControllerButtonEvent and maps the fields of:
   * which  - the joystick instance id
   * button - the controller button (SDL_GameControllerButton)
   * state  - SDL_PRESSED or SDL_RELEASED
   * into a single Uint64
   */ 
  Uint64 HandleEvent(SDL_ControllerButtonEvent e);
  
  void InitJoyCons();
  static int NumJoyCons();
  void Free();
private:
  int maxJoyCons;
  SDL_GameController *joycon[];
};
