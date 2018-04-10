#include "chainbar.h"
#include "math.h"

// init variables to zero
float chainbar_angle = 0;
bool pid_chainbar_disabled = false;

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
  pid_chainbar.init(6.6f, 0.f, 700.f, CHAINBAR_STACK, chainbar_angle);
  pid_chainbar.target_buffer = 1.5f;
  pid_chainbar.max_d = 200;
}

// updates all chainbar motors' data
void chainbarUpdateMotorData() {
  motor_chainbar.updateData(chainbar_angle, UPDATE_INTERVAL);
}

// update all chainbar chainbarer motors
void chainbarUpdateMotors() {
  motor_chainbar.updateMotor(UPDATE_INTERVAL);
}

// update all chainbar chainbarer sensors
void chainbarUpdateSensors() {

  // angle (degrees) of the chainbar
  chainbar_angle = (analogRead(POT_CHAINBAR) - 1383) * .0634765625f;
}

// determines whether or not the chainbar has reached its target
bool chainbarAtTarget(bool vel) {
  if (pid_chainbar.getTarget() == CHAINBAR_GRAB && chainbar_angle < CHAINBAR_GRAB + 10) return true;
  else return pid_chainbar.atTarget(vel, chainbar_angle, motor_chainbar.getVelocity());
}

// returns a recommended timeout for a PID
unsigned int chainbarGetTimeout(float target) {
  // float delta = abs(target - chainbar_angle);
  // return delta * 15.f;
  return 1500;
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
