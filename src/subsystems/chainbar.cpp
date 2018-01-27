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
  pid_chainbar.init(15.2f, .1f, 650.f, CHAINBAR_STACK, chainbar_angle);
  pid_chainbar.kp_rev = 1.5f;
  pid_chainbar.ki_rev = .1f;
  pid_chainbar.kd_rev = 25.f;
  pid_chainbar.target_buffer = 3.f;
}

// update all chainbar chainbarer motors
void chainbarUpdateMotors() {
  motor_chainbar.update(chainbar_angle, UPDATE_INTERVAL);
}

// update all chainbar chainbarer sensors
void chainbarUpdateSensors() {

  // angle (degrees) of the chainbar
  chainbar_angle = analogRead(POT_CHAINBAR) * .0634765625f;
}

// determines whether or not the chainbar has reached its target
bool chainbarAtTarget(bool vel) {
  if (pid_chainbar.getTarget() == CHAINBAR_GRAB && chainbar_angle < CHAINBAR_GRAB + 10) return true;
  else return pid_chainbar.atTarget(vel, chainbar_angle, motor_chainbar.getVelocity());
}

// returns a recommended timeout for a PID
unsigned int chainbarGetTimeout(float target) {
  // float delta = abs(target - chainbar_angle);
  // return delta * 27.52f;
  return 3000;
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
