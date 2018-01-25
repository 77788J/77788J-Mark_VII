#include "chainbar.h"
#include "math.h"

// init variables to zero
float chainbar_angle = 0;

// declare motor
Motor motor_chainbar;

// declare PID
Pid pid_chainbar;

// inits the chainbar (motors, pid, etc.)
void chainbarInit() {

  // update sensors for accurate starting position
  chainbarUpdateSensors();

  // init motor
  motor_chainbar.init(MOTOR_CHAINBAR, true, chainbar_angle);

  // init PID
  pid_chainbar.init(10.f, 5.f, 100.f, CHAINBAR_GRAB, chainbar_angle);
  pid_chainbar.target_buffer = 2.f;
}

// update all chainbar chainbarer motors
void chainbarUpdateMotors() {
  motor_chainbar.update(chainbar_angle, UPDATE_INTERVAL);
}

// update all chainbar chainbarer sensors
void chainbarUpdateSensors() {

  // angle (degrees) if the chainbar
  chainbar_angle = analogRead(POT_CHAINBAR) * .0634765625f;
}

// determines whether or not the chainbar has reached its target
bool chainbarAtTarget(bool vel) {
  return pid_chainbar.atTarget(vel, chainbar_angle, motor_chainbar.getVelocity());
}

// returns a recommended timeout for a PID
unsigned int chainbarGetTimeout(float target) {
  float delta = abs(target - chainbar_angle);
  return delta * (fabs(CHAINBAR_GRAB - CHAINBAR_STACK) * .002f);
}

// sets the power of both chainbar motors
void chainbarSetPower(int power) {
  motor_chainbar.setPower(power);
}

void chainbarGoto(float angle, bool wait, bool vel) {

  // setup timeout
  unsigned int timeout = 0;
  unsigned int max_timeout = chainbarGetTimeout(pid_chainbar.getTarget());

  // update PID target
  pid_chainbar.setTarget(angle);

  // wait if applicable
  if (wait) {
    while (!chainbarAtTarget(vel) && timeout < max_timeout) {
      delay(1);
      timeout += 1;
    }
  }
}
