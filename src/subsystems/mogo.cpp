#include "mogo.h"

// init variables to zero
float mogo_angle_l = 0;
float mogo_angle_r = 0;
float mogo_angle = 0;

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
  pid_mogo.init(1, .75f, 3, mogo_angle, mogo_angle);
}

// update all mogo lifter motors
void mogoUpdateMotors() {
  motor_mogo.update(mogo_angle, UPDATE_INTERVAL);
}

// update all mogo lifter sensors
void mogoUpdateSensors() {

  // update left potentiometer
  float raw_l = 3140 - analogRead(POT_MOGO_L); // translate to correct range
  mogo_angle_l = (mogo_angle_l * .4f) + (raw_l * 0.087890625f * .6f); // convert to degrees and apply filter

  // update left potentiometer
  float raw_r = analogRead(POT_MOGO_R) - 963; // translate to correct range
  mogo_angle_r = (mogo_angle_r * .4f) + (raw_r * 0.087890625f * .6f); // convert to degrees and apply filter

  // average left and right potentiometers
  mogo_angle = (mogo_angle_l + mogo_angle_r) * .5f;
}

// sets the power of both mogo motors
void mogoSetPower(int power) {
  motor_mogo.setPower(power);
}

void mogoGoto(float angle, bool wait, bool vel) {

  // update PID target
  pid_mogo.setTarget(angle);

  // wait if applicable
  if (wait) {
    while (pid_mogo.atTarget(vel, mogo_angle, motor_mogo.getVelocity())) {
      delay(1);
    }
  }
}
