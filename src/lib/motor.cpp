#include "motor.h"
#include "math.h"

// trueSpeed array (taken from team 24C)
int true_speed[101] = {
   0,
   0,   0,   0,   0,   0,   0,   0,   0,  17,  17,
  17,  17,  18,  19,  19,  20,  20,  20,  20,  21,
  22,  22,  22,  23,  24,  24,  24,  24,  25,  25,
  26,  26,  27,  27,  28,  28,  28,  28,  29,  29,
  29,  30,  31,  31,  31,  31,  32,  32,  33,  34,
  35,  35,  35,  36,  36,  37,  38,  38,  39,  39,
  40,  41,  41,  42,  43,  44,  45,  45,  46,  47,
  48,  50,  50,  51,  52,  53,  54,  55,  56,  57,
  57,  58,  61,  61,  62,  62,  64,  65,  66,  66,
  68,  69,  69,  69,  70,  85,  90, 100, 100, 100
};

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
  slew = true;
  slew_rate = .667f;
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
  target_power = p;
  if (!slew) power = p;
}

// updates the motor (physical motor and internal variables)
void Motor :: update(float angle, int interval) {

  // slew motor of applicable
  if (slew) {
    float power_change = min(slew_rate * (float) interval, fabs(target_power - power)); // calculate change in power
    power += power_change * sign(target_power - power); // apply correct sign and add to power var
  }

  // make sure power is in confines of reality
  power = limit(power, -100, 100);

  // move physical motor at specified power
  int p = round(power); // store power in temporary variable
  if (reversed) p = -power; // reverse if necessary
  motorSet(port, true_speed[abs(p)] * sign(p)); // set the actualy power (using trueSpeed)

  // update velocity (with moving average filter)
  float rpm = calcRpm(angle - prev, interval); // calculate RPM
  velocity = (velocity * .6f) + (rpm * .4f); // apply moving average filter and store in velocity variable

  // uodate previous angle for next run
  prev = angle;
}
