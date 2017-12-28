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

  // make sure power is in confines of reality
  power = limit(power, -100, 100);

  // move physical motor at specified power
  int p = power; // store power in temporary variable
  if (reversed) p = -power; // reverse if necessary
  if (abs(p) < 10) p = 0; // if the power is ~0, just give it 0
  motorSet(port, p); // set the actualy power

  // update velocity (with moving average filter)
  float error = angle - prev; // change in angle
  float rpm = (error * 166.67) / interval; // convert error to RPM
  velocity = (velocity * .6f) + (rpm * .4f); // apply moving average filter and store in velocity variable

  // uodate previous angle for next run
  prev = angle;
}
