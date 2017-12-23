#include "motor.h"

// default initializer
Motor :: Motor() {}

// motor "factory"
// actually initializes motor properties
void Motor :: init(int port_, bool reversed_, float angle_) {
  port = port_;
  reversed = reversed_;
  prev = angle_;
  power = 0;
  velocity = 0;
}

// gets the current power of the motor
int Motor :: getPower() {
  return power;
}

// gets the current velocity of the motor
float Motor :: getVelocity() {
  return velocity;
}

// sets the power of the motor
void Motor :: setPower(int p) {
  power = p;
}

// updates the motor (physical motor and internal variables)
void Motor :: update(float angle, int interval) {

  // move physical motor at specified power
  if (reversed) motorSet(port, -power);
  else motorSet(port, power);

  // update velocity (with moving average filter)
  float error = angle - prev; // change in angle
  float rpm = (error * 166.67) / interval; // convert error to RPM
  velocity = (velocity * .6f) + (rpm * .4f); // apply moving average filter and store in velocity variable

  // uodate previous angle for next run
  prev = angle;
}
