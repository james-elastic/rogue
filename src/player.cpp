#include <iostream>
#include <SDL2/SDL.h>

#include "player.h"

Player::Player() {
  this->axisLeftX    = 0x0000u;
  this->axisLeftY    = 0x0000u;
  this->axisRightX   = 0x0000u;
  this->axisRightY   = 0x0000u;
  this->triggerLeft  = 0x0000u;
  this->triggerRight = 0x0000u;
  this->buttonState  = 0x0000u;
}

Player::~Player() {

}

void Player::ResetButtonState() {
  this->buttonState = 0x0000u;
}

void Player::UpdateState(SDL_ControllerButtonEvent cbe) {
  /*std::cout << "type: " << cbe.type << " ts: " << cbe.timestamp
	    << " which: " << cbe.which << " button: " << cbe.button
	    << " state: " << cbe.state << "\n";
  if(cbe.state == SDL_PRESSED || cbe.state == SDL_RELEASED) {
    std::cout << "pressedorreleased" << "\n";
  } else {
    std::cout << "some other state" << "\n";
    }*/
  switch(cbe.button) {
  case SDL_CONTROLLER_BUTTON_A: this->buttonState ^= BUTTON_A; break;
  case SDL_CONTROLLER_BUTTON_B: this->buttonState ^= BUTTON_B; break;
  case SDL_CONTROLLER_BUTTON_X: this->buttonState ^= BUTTON_X; break;
  case SDL_CONTROLLER_BUTTON_Y: this->buttonState ^= BUTTON_Y; break;
  case SDL_CONTROLLER_BUTTON_BACK: this->buttonState ^= BUTTON_BACK; break;
  case SDL_CONTROLLER_BUTTON_GUIDE: this->buttonState ^= BUTTON_GUIDE; break;
  case SDL_CONTROLLER_BUTTON_START: this->buttonState ^= BUTTON_START; break;
  case SDL_CONTROLLER_BUTTON_LEFTSTICK:
    this->buttonState ^= BUTTON_LEFTSTICK; break;
  case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
    this->buttonState ^= BUTTON_RIGHTSTICK; break;
  case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
    this->buttonState ^= BUTTON_LEFTSHOULDER; break;
  case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
    this->buttonState ^= BUTTON_RIGHTSHOULDER; break;
  case SDL_CONTROLLER_BUTTON_DPAD_UP:
    this->buttonState ^= BUTTON_DPAD_UP; break;
  case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
    this->buttonState ^= BUTTON_DPAD_DOWN; break;
  case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
    this->buttonState ^= BUTTON_DPAD_LEFT; break;
  case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
    this->buttonState ^= BUTTON_DPAD_RIGHT; break;
  case SDL_CONTROLLER_BUTTON_MAX: this->buttonState ^= BUTTON_MAX; break;
  }
}

Uint16 Player::GetButtonState() {
  return this->buttonState;
}

void Player::UpdateState(SDL_ControllerAxisEvent cae) {

}
