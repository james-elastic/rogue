#include <SDL2/SDL.h>

/* Simplify and define the state changes available to the player from the
 * SDL_ControllerButtonEvent */
#define BUTTON_A             0x0001u
#define BUTTON_B             0x0002u
#define BUTTON_X             0x0004u
#define BUTTON_Y             0x0008u
#define BUTTON_BACK          0x0010u
#define BUTTON_GUIDE         0x0020u
#define BUTTON_START         0x0040u
#define BUTTON_LEFTSTICK     0x0080u
#define BUTTON_RIGHTSTICK    0x0100u
#define BUTTON_LEFTSHOULDER  0x0200u
#define BUTTON_RIGHTSHOULDER 0x0400u
#define BUTTON_DPAD_UP       0x0800u
#define BUTTON_DPAD_DOWN     0x1000u
#define BUTTON_DPAD_LEFT     0x2000u
#define BUTTON_DPAD_RIGHT    0x4000u
#define BUTTON_MAX           0x8000u

class Player {
public:
  Player();
  ~Player();

  void UpdateState(SDL_ControllerButtonEvent cbe);
  Uint16 GetButtonState();
  void ResetButtonState();
  void UpdateState(SDL_ControllerAxisEvent cae);
private:
  // Internal mapping for SDL_ControllerAxisEvent states
  Uint16 axisLeftX;
  Uint16 axisLeftY;
  Uint16 axisRightX;
  Uint16 axisRightY;
  Uint16 triggerLeft;
  Uint16 triggerRight;

  // Internal mapping for SDL_ControllerButtonEvent states
  Uint16 buttonState;
};
