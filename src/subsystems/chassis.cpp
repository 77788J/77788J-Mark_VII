#include "chassis.h"

// init mode to direct
int chassis_mode = CHASSIS_MODE_DIRECT;

// init variables to zero
float chassis_left = 0;
float chassis_right = 0;
float chassis_angle = 0;

// declare motors
Motor motor_chassis_fl;
Motor motor_chassis_bl;
Motor motor_chassis_fr;
Motor motor_chassis_br;

// declare encoders
Encoder enc_chassis_l;
Encoder enc_chassis_r;

// declare gyros
Gyro gyro_a;
Gyro gyro_b;

// declare PIDs
Pid pid_chassis_l;
Pid pid_chassis_r;
Pid pid_chassis_theta;

// inits the chassis (PID, encoders, etc)
void chassisInit() {

  // init motors
  motor_chassis_fl.init(5, true, 0);
  motor_chassis_bl.init(2, true, 0);
  motor_chassis_fr.init(6, false, 0);
  motor_chassis_br.init(9, false, 0);

  // init gyros
  gyro_a = gyroInit(6, 196);
  gyro_b = gyroInit(7, 196);

  // init encoders
  enc_chassis_l = encoderInit(1, 2, true);
  enc_chassis_r = encoderInit(3, 4, false);

  // init PIDs
  pid_chassis_l.init(5, 5, 30, 0, 0);
  pid_chassis_r.init(5, 5, 30, 0, 0);
  pid_chassis_theta.init(1, 0, 0, 0, 0);
}

// update all chassis motors
void chassisUpdateMotors() {
  motor_chassis_fl.update(chassis_left, UPDATE_INTERVAL);
  motor_chassis_bl.update(chassis_left, UPDATE_INTERVAL);
  motor_chassis_fr.update(chassis_right, UPDATE_INTERVAL);
  motor_chassis_br.update(chassis_right, UPDATE_INTERVAL);
}

// update all chassis sensors
void chassisUpdateSensors() {

  // encoder degrees
  chassis_left = (float) encoderGet(enc_chassis_l) * .333f;
  chassis_right = (float) encoderGet(enc_chassis_r) * .333f;

  // orientation
  float chassis_angle_encoders = (chassis_left - chassis_right) * 0;
  float chassis_angle_gyros = (float) (gyroGet(gyro_a) + gyroGet(gyro_b)) * .5f;
  chassis_angle = (chassis_angle_encoders * .5f) + (chassis_angle_gyros * .5f);
}

// reset all chassis sensors
void chassisResetSensors() {

  // encoders
  encoderReset(enc_chassis_l);
  encoderReset(enc_chassis_r);

  // gyros
  gyroReset(gyro_a);
  gyroReset(gyro_b);

  // variables
  chassis_left = 0;
  chassis_right = 0;
  chassis_angle = 0;
}

// set the power of the left side of the chassis
void chassisSetPowerL(int power) {
  motor_chassis_fl.setPower(power);
  motor_chassis_bl.setPower(power);
}

// set the power of the right side of the chassis
void chassisSetPowerR(int power) {
  motor_chassis_fr.setPower(power);
  motor_chassis_br.setPower(power);
}

// set the power of both sides of the chassis
void chassisSetPower(int power) {
  chassisSetPowerL(power);
  chassisSetPowerR(power);
}

// set the power of both sides of the chassis individually
void chassisSetPowerExt(int l, int r) {
  chassisSetPowerL(l);
  chassisSetPowerR(r);
}

// move the chassis (uses PIDs)
void chassisMove(float l, float r, bool wait, bool vel) {

  // backup current chassis mode
  int prev_chassis_mode = chassis_mode;

  // update chassis mode
  chassis_mode = CHASSIS_MODE_POSITION;

   // set target variables (relative to current state)
  float target_l = chassis_left + l;
  float target_r = chassis_right + r;

  // set PID targets
  pid_chassis_l.setTarget(target_l);
  pid_chassis_r.setTarget(target_r);

  // wait for chassis to have moved (if applicable)
  if (wait) {
    while (!(pid_chassis_l.atTarget(vel) || pid_chassis_r.atTarget(vel))) {
      delay(1);
    }

    // restore original chassis mode (only if waited, obviously)
    chassis_mode = prev_chassis_mode;
  }
}

// rotates the chassis (uses PIDs)
void chassisRotate(float theta, bool wait, bool vel) {

  // backup current chassis mode
  int prev_chassis_mode = chassis_mode;

  // update chassis mode
  chassis_mode = CHASSIS_MODE_ANGLE;

   // set target variable (relative to current state)
  float target = chassis_angle + theta;

  // set PID target
  pid_chassis_theta.setTarget(target);

  // wait for chassis to have rotated (if applicable)
  if (wait) {
    while (!pid_chassis_theta.atTarget(vel)) {
      delay(1);
    }

    // restore original chassis mode (only if waited, obviously)
    chassis_mode = prev_chassis_mode;
  }
}
