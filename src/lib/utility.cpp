#include "utility.h"
#include "math.h"

float limit(float val, float min, float max) {
  if (val > max) return max;
  if (val < min) return min;
  return val;
}

float wrap(int val, int min, int max) {
  return min + ((val - min) % (max - min));
}

void waitForJoystickUpdate(Joystick joy, int reference) {
  while (joy.updated < reference) {
    delay(1);
  }
}
