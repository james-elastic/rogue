#include <stdio.h>

#include "controller.h"
#include "log.h"

/* Controller class to act as a set of "pure" functions to handle input
 * and output from controller objects (eg Xbox360). We called the class
 * JoyCon to represent we handle this should handle Joysticks and 
 * Controllers (and its a play on the Nintendo Switch JoyCon).
 *
 * Useful links on why we use the SDL_GameController* classes vs 
 * SDL_Joystick* 
 * - https://wiki.libsdl.org/CategoryGameController
 * - https://stackoverflow.com/a/50026410
 */


JoyCon::JoyCon() {
  this->maxJoyCons = 4;
}

JoyCon::JoyCon(int maxJoyConsAllowed) {
  // Init
  this->maxJoyCons = maxJoyConsAllowed;
}

JoyCon::~JoyCon() {
  // Free
  this->Free();
}

void JoyCon::InitJoyCons() {
  int maxJoyCons = this->maxJoyCons;
  int numJoyCons = this->NumJoyCons();
  
  if(numJoyCons < maxJoyCons) {
    maxJoyCons = numJoyCons;
  }
  
  for(int i = 0; i < maxJoyCons; ++i) {
    joycon[i] = SDL_GameControllerOpen( i );
    if(joycon[i] == NULL) {
      Log::Error(SDL_GetError());
    }
  }
}

int JoyCon::NumJoyCons() {
  return SDL_NumJoysticks();
}

void JoyCon::Free() {
  for(int i = 0; i < this->maxJoyCons; ++i) {
    if(this->joycon[i] != NULL) {
      SDL_GameControllerClose( joycon[i] );
      joycon[i] = NULL;
    }
  }
}
