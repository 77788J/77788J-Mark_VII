#ifndef BUTTON_MANAGER_H_
#define BUTTON_MANAGER_H_
#include <joystick.h>

// declare joystick(s)
extern Joystick joystick;

// init all joysticks
// to be called from init.cpp
void initJoysticks();

// update all joysticks
void updateJoysticks();

#endif
