#include "motor.h"

// default initializer
Motor :: Motor() {}

void Motor :: init(int port_, bool reversed_, float angle_) {
  port = port_;
  reversed = reversed_;
  prev = angle_;
  power = 0;
  velocity = 0;
}
