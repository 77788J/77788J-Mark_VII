#include "claw.h"
#include "math.h"

// init variables to zero
float claw_angle = 0;
float claw_height = 0;

// declare motor
Motor motor_claw;

// declare PID
Pid pid_claw;

// inits the claw clawer (motors, pid, etc.)
void clawInit() {

  // update sensors for accurate starting position
  clawUpdateSensors();

  // init motor
  motor_claw.init(MOTOR_CLAW, false, claw_angle);

  // init PID
  pid_claw.init(1.15f, 0, 10, CLAW_CLOSED, claw_angle);
  pid_claw.target_buffer = 20;
}

// update all claw clawer motors
void clawUpdateMotorData() {
  motor_claw.updateData(claw_angle, UPDATE_INTERVAL);
}

// update all claw clawer motors
void clawUpdateMotors() {
  motor_claw.updateMotor(UPDATE_INTERVAL);
}

// update all claw clawer sensors
void clawUpdateSensors() {

  // angle (degrees) if the claw
  claw_angle = analogRead(POT_CLAW) * .0634765625f;
}

// determines whether or not the claw has reached its target
bool clawAtTarget(bool vel) {
  return pid_claw.atTarget(vel, claw_angle, motor_claw.getVelocity());
}

// returns a recommended timeout for a PID
unsigned int clawGetTimeout(float target) {
  float delta = abs(target - claw_height);
  return delta * (500 / abs(CLAW_OPEN - CLAW_CLOSED));
}

// sets the power of both claw motors
void clawSetPower(int power) {
  motor_claw.setPower(power);
}

void clawGoto(float angle, bool wait, bool vel) {

  // setup timeout
  unsigned int timeout = 0;
  unsigned int max_timeout = clawGetTimeout(pid_claw.getTarget());

  // update PID target
  pid_claw.setTarget(angle);

  // wait if applicable
  if (wait) {
    while (!clawAtTarget(vel) && timeout < max_timeout) {
      delay(1);
      timeout += 1;
    }
  }
}
