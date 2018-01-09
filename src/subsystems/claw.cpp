#include "claw.h"
#include "math.h"

// init variables to zero
float claw_angle = 0;
float claw_height = 0;

// declare motor
Motor motor_claw;

// declare encoder
Encoder enc_claw;

// declare PID
Pid pid_claw;

// inits the claw clawer (motors, pid, etc.)
void clawInit() {

  // define claw encoder
  enc_claw = encoderInit(5, 6, false);

  // update sensors for accurate starting position
  clawUpdateSensors();

  // init motor
  motor_claw.init(MOTOR_CLAW, true, claw_angle);

  // init PID
  pid_claw.init(20.f, 10, 56, CLAW_CLOSED, claw_angle);
  pid_claw.target_buffer = 20;
}

// update all claw clawer motors
void clawUpdateMotors() {
  motor_claw.update(claw_angle, UPDATE_INTERVAL);
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
  motor_claw.setPower(power, false);
}

void clawGoto(float angle, bool wait, bool vel) {

  // update PID target
  pid_claw.setTarget(angle);

  // wait if applicable
  if (wait) {
    while (!clawAtTarget(vel)) {
      delay(1);
    }
  }
}
