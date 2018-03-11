#include "mogo.h"
#include "math.h"

// init variables to zero
float mogo_angle_l = 0;
float mogo_angle_r = 0;
float mogo_angle = 0;

bool pid_mogo_enabled = true;
bool mogo_dead = false;

// declare motor
Motor motor_mogo;

// declare PID
Pid pid_mogo;

// inits the mogo lifter (motors, pid, etc.)
void mogoInit() {

  // update sensors for accurate starting position
  mogoUpdateSensors();

  // init motor
  motor_mogo.init(MOTOR_MOGO, true, mogo_angle);

  // init PID
  pid_mogo.init(2.83, 0.f, 16.f, MOGO_ANGLE_GRAB, mogo_angle);
  pid_mogo.kc = 20.f;
  pid_mogo.target_buffer = 15;
}

// update all mogo lifter motors
void mogoUpdateMotorData() {
  motor_mogo.updateData(mogo_angle, UPDATE_INTERVAL);
}

// update all mogo lifter motors
void mogoUpdateMotors() {
  motor_mogo.updateMotor(UPDATE_INTERVAL);
}

// update all mogo lifter sensors
void mogoUpdateSensors() {

  // update left potentiometer
  float raw_l = 975.f - analogRead(POT_MOGO_L); // translate to correct range
  mogo_angle_l = (mogo_angle_l * .4f) + (raw_l * 0.088890625f * .6f); // convert to degrees and apply filter

  // update left potentiometer
  float raw_r = analogRead(POT_MOGO_R) - 3305.f; // translate to correct range
  mogo_angle_r = (mogo_angle_r * .4f) + (raw_r * 0.088890625f * .6f); // convert to degrees and apply filter

  // average left and right potentiometers
  mogo_angle = (mogo_angle_l + mogo_angle_r) * .5f + 27.f;
}

// determines whether or not the mogo lifter has reached its target
bool mogoAtTarget(bool vel) {
  if (pid_mogo.getTarget() == MOGO_ANGLE_EXTENDED && mogo_angle > MOGO_ANGLE_EXTENDED + 20)
    return true;
  else if (pid_mogo.getTarget() == MOGO_ANGLE_RETRACTED && mogo_angle < MOGO_ANGLE_EXTENDED - 20)
    return true;
  else
    return pid_mogo.atTarget(vel, mogo_angle, motor_mogo.getVelocity());
}

// returns a recommended timeout for a PID
unsigned int mogoGetTimeout(float target) {
  float delta = abs(target - mogo_angle);
  return delta * 7.5f;
}

// sets the power of both mogo motors
void mogoSetPower(int power) {
  motor_mogo.setPower(power);
}

void mogoGoto(float angle, bool wait, bool vel) {

  // setup timeout
  unsigned int timeout = 0;
  unsigned int max_timeout = mogoGetTimeout(pid_mogo.getTarget());

  // update PID target
  pid_mogo.setTarget(angle);

  // wait if applicable
  if (wait) {
    while (!mogoAtTarget(vel) && timeout < max_timeout) {
      delay(1);
      timeout += 1;
    }
  }
}
