#ifndef UTILITY_H_
#define UTILITY_H_
#include <main.h>
#include <joystick.h>

float limit(float val, float min, float max);
float wrap(float val, float min, float max);
void waitForJoystickUpdate(Joystick joy, int reference);

#endif
