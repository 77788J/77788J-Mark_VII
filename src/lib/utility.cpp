#include "utility.h"
#include "math.h"

int sign(float x) {
  return (x > 0) - (x < 0);
}

float limit(float val, float min, float max) {
  if (val > max) return max;
  if (val < min) return min;
  return val;
}

float wrap(int val, int min, int max) {
  return min + ((val - min) % (max - min));
}

float calcRpm(float error, int interval) {
  return (error * 166.67) / interval;
}
