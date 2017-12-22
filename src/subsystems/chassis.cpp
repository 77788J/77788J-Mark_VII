#include "chassis.h"
#include "pid.h"
#include "motor.h"

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

// declare PIDs
Pid pid_chassis_l;
Pid pid_chassis_r;

// inits the chassis (PID, encoders, etc)
void chassisInit() {

  // init motors
  motor_chassis_fl.init(5, false, 0);
  motor_chassis_bl.init(2, false, 0);
  motor_chassis_fr.init(6, false, 0);
  motor_chassis_br.init(9, false, 0);

  // init encoders
  enc_chassis_l = encoderInit(1, 2, false);
  enc_chassis_r = encoderInit(3, 4, false);

  // init PIDs
  pid_chassis_l.init(1, 0, 0, 0, 0, 0);
  pid_chassis_r.init(1, 0, 0, 0, 0, 0);
}

// update all chassis motors
void chassisUpdateMotors() {
  // motor_chassis_fl.update(float angle, UPDATE_INTERVAL);
  // motor_chassis_bl.update(float angle, UPDATE_INTERVAL);
  // motor_chassis_fr.update(float angle, UPDATE_INTERVAL);
  // motor_chassis_br.update(float angle, UPDATE_INTERVAL);
}

// update all chassis sensors
void chassisUpdateSensors() {
  chassis_left = (float) encoderGet(enc_chassis_l) * .333f;
  chassis_right = (float) encoderGet(enc_chassis_r) * .333f;
  chassis_angle = (chassis_left - chassis_right) * 0;
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

void chassisMove(float l, float r, bool wait, bool vel) {

   // set target variables (relative to current state)
  float target_l = chassis_left + l;
  float target_r = chassis_right + r;

  // set PID targets
  pid_chassis_l.setTarget(target_l);
  pid_chassis_r.setTarget(target_r);

  if (wait) {
    while (!(pid_chassis_l.atTarget(vel) || pid_chassis_r.atTarget(vel))) {
      delay(1);
    }
  }
}
