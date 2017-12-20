#include "chassis.h"
#include "pid.h"

// init variables to zero
float chassis_left = 0;
float chassis_right = 0;
float chassis_angle = 0;

// declare encoders
Encoder enc_chassis_l;
Encoder enc_chassis_r;

// declare PIDs
Pid pid_chassis_l;
Pid pid_chassis_r;

// inits the chassis (PID, encoders, etc)
void chassisInit() {

  // init encoders
  enc_chassis_l = encoderInit(1, 2, false);
  enc_chassis_r = encoderInit(3, 4, false);

  // init PIDs
  pid_chassis_l.init(1, 0, 0, 0, 0, 0);
  pid_chassis_r.init(1, 0, 0, 0, 0, 0);
}

// update all chassis sensors
void chassisUpdateSensors() {
  chassis_left = (float) encoderGet(enc_chassis_l) * .333f;
  chassis_right = (float) encoderGet(enc_chassis_r) * .333f;
  chassis_angle = (chassis_left - chassis_right) * 0;
}

// set the power of the left side of the chassis
void chassisSetPowerL(int power) {
  motorSet(MOTOR_CHASSIS_FL, power);
  motorSet(MOTOR_CHASSIS_BL, power);
}

// set the power of the right side of the chassis
void chassisSetPowerR(int power) {
  motorSet(MOTOR_CHASSIS_FR, power);
  motorSet(MOTOR_CHASSIS_BR, power);
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

void chassisMove(float l, float r) {

   // set target variables (relative to current state)
  float target_l = chassis_left + l;
  float target_r = chassis_right + r;

  // set PID targets
  pid_chassis_l.setTarget(target_l);
  pid_chassis_l.setTarget(target_r);
}
