#include "chassis.h"
#include "math.h"

// init mode to direct
int chassis_mode = CHASSIS_MODE_DIRECT;

// init variables to zero
float chassis_left = 0;
float chassis_right = 0;
float chassis_angle = 0;
float orientation_ap = 0;
bool line_l = false;
bool line_r = false;

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

// declare AP filter
ApFilterInput input_gyro_a;
ApFilterInput input_gyro_b;
ApFilterInput input_encoders;
ApFilter ap_filter_orientation;

// declare PIDs
Pid pid_chassis_l;
Pid pid_chassis_r;
Pid pid_chassis_theta;

// inits the chassis (PID, encoders, etc)
void chassisInit() {

  // init motors
  motor_chassis_fl.init(MOTOR_CHASSIS_FL, false, 0);
  motor_chassis_bl.init(MOTOR_CHASSIS_BL, true, 0);
  motor_chassis_fr.init(MOTOR_CHASSIS_FR, true, 0);
  motor_chassis_br.init(MOTOR_CHASSIS_BR, false, 0);

  // init gyros
  gyro_a = gyroInit(6, 196);
  gyro_b = gyroInit(7, 188);

  // init encoders
  enc_chassis_l = encoderInit(1, 2, true);
  enc_chassis_r = encoderInit(3, 4, true);

  // init AP inputs
  float g[6] =  {.0018f, -.0367f, .2798f, -.9749f, 1.51f, .1033f}; // y = 0.0018x5 - 0.0367x4 + 0.2798x3 - 0.9749x2 + 1.51x + 0.1033
  float enc[1] =  {.3f};
  input_gyro_a.init(3, g);
  input_gyro_b.init(3, g);
  input_encoders.init(1, enc);

  // create array of AP filter inputs
  ApFilterInput inputs[3] = {
    input_gyro_a,
    input_gyro_b,
    input_encoders
  };

  // init AP filter
  ap_filter_orientation.init(.001f, 3, inputs);

  // init PIDs
  pid_chassis_l.init(.4f, 10, 200, 0, 0);
  pid_chassis_r.init(.4f, 10, 200, 0, 0);
  pid_chassis_l.max_d = 150;
  pid_chassis_r.max_d = 150;
  pid_chassis_l.target_buffer = 8.f;
  pid_chassis_r.target_buffer = 8.f;

  pid_chassis_theta.init(2.8f, 4, 600, 0, 0);
  pid_chassis_theta.target_buffer = 1.24f;
  pid_chassis_theta.velocity_buffer = 3;
  pid_chassis_theta.max_d = 200;
}

// updates all chainbar motors' data
void chassisUpdateMotorData() {
  motor_chassis_fl.updateData(chassis_left, UPDATE_INTERVAL);
  motor_chassis_bl.updateData(chassis_left, UPDATE_INTERVAL);
  motor_chassis_fr.updateData(chassis_right, UPDATE_INTERVAL);
  motor_chassis_br.updateData(chassis_right, UPDATE_INTERVAL);
}

// update all chassis motors
void chassisUpdateMotors() {
  motor_chassis_fl.updateMotor(UPDATE_INTERVAL);
  motor_chassis_bl.updateMotor(UPDATE_INTERVAL);
  motor_chassis_fr.updateMotor(UPDATE_INTERVAL);
  motor_chassis_br.updateMotor(UPDATE_INTERVAL);
}

// update all chassis sensors
void chassisUpdateSensors() {

  // encoder degrees
  chassis_left = (float) encoderGet(enc_chassis_l);
  chassis_right = (float) encoderGet(enc_chassis_r);

  // orientation
  float chassis_angle_encoders = (chassis_left - chassis_right) * .2617f; // multiply by a scalar to convert to degrees
  float a = gyroGet(gyro_a);
  float b = gyroGet(gyro_b);
  float chassis_angle_gyros = (a * 1.f) + (b * 0.f);

  // calculate orientation from weighted average
  chassis_angle = (chassis_angle_encoders * 0.f) + (chassis_angle_gyros * 1.f);

  // determine whether or not each line tracker is over a white line
  line_l = (analogRead(LINE_L) < 500);
  line_r = (analogRead(LINE_R) < 500);
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

// returns whether or not the chassis has reached its target
bool chassisAtTarget(bool vel, int mode) {
  switch (mode) {

    case (CHASSIS_MODE_POSITION):
      return (pid_chassis_l.atTarget(vel, chassis_left,  motor_chassis_fl.getVelocity()) &&
              pid_chassis_r.atTarget(vel, chassis_right, motor_chassis_fr.getVelocity()));
      break;

    case (CHASSIS_MODE_ANGLE):
      return pid_chassis_theta.atTarget(vel, chassis_angle, (fabs(motor_chassis_fl.getVelocity()) + fabs(motor_chassis_fr.getVelocity())) * .5f);
      break;

    default:
      return false;
      break;

    }
}

// returns a recommended timeout for a position PID
unsigned int chassisGetTimeoutPosition(float l, float r) {
  float dist = max(abs(l), abs(r));
  return dist * 36.75f + 2.75f;
}

// returns a recommended timeout for a rotation PID
unsigned int chassisGetTimeoutAngle(float theta) {
  return abs(theta * 12.5f + 2.f);
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

  int max_timeout = chassisGetTimeoutPosition(l, r);
  int timeout = 0;

  // backup current chassis mode
  int prev_chassis_mode = chassis_mode;

  // update chassis mode
  chassis_mode = CHASSIS_MODE_POSITION;

   // set target variables (relative to current state)
  float target_l = chassis_left  + (l * CHASSIS_SCALE_DISTANCE);
  float target_r = chassis_right + (r * CHASSIS_SCALE_DISTANCE);

  // set PID targets
  pid_chassis_l.setTarget(target_l);
  pid_chassis_r.setTarget(target_r);

  // wait for chassis to have moved (if applicable)
  if (wait) {
    while (!chassisAtTarget(vel, CHASSIS_MODE_POSITION) && timeout < max_timeout) {
      delay(1);
      timeout++;
    }

    // restore original chassis mode (only if waited, obviously)
    chassis_mode = prev_chassis_mode;
    chassisSetPower(0);
  }
}

// rotates the chassis (uses PIDs)
void chassisRotate(float theta, bool wait, bool vel) {

  int max_timeout = chassisGetTimeoutAngle(theta);
  int timeout = 0;

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
    while (!chassisAtTarget(vel, CHASSIS_MODE_ANGLE) && timeout < max_timeout) {
      delay(1);
      timeout++;
    }

    // restore original chassis mode (only if waited, obviously)
    pid_chassis_l.setTarget(chassis_left);
    pid_chassis_r.setTarget(chassis_right);
    chassis_mode = prev_chassis_mode;
    chassisSetPower(0);
  }
}
