#include "button_manager.h"

// declare joystick(s)
Joystick joystick;

// initialize all joysticks
// to be called from init.cpp
void initJoysticks() {
  joystick.init(1);
}

// update all joysticks
void updateJoysticks() {
  joystick.update();
}
