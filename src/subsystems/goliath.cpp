#include "goliath.h"

// motors
Motor motor_goliath;

// encoder
Encoder enc_goliath;

// PID
Pid pid_goliath;

// variables
unsigned char goliath_mode = GOLIATH_MODE_INTAKE; // default to intake mode
bool goliath_holding = false; // is it currently holding a cone?
bool goliath_spinning = false; // logs whether or not it is spinning
float goliath_angle = 0;

// inits the goliath (PID, motors, etc)
void goliathInit() {

  // define goliath encoder
  enc_goliath = encoderInit(7, 8, false);

  // init motor
  motor_goliath.init(MOTOR_GOLIATH, false, goliath_angle);
  motor_goliath.slew = true;
  motor_goliath.slew_rate = .25f;

  // init PID
  pid_goliath.init(1.6f, 0.f, 0.f, goliath_angle, goliath_angle);
}

// update all goliath motor data
void goliathUpdateMotorData() {
  motor_goliath.updateData(goliath_angle, UPDATE_INTERVAL);
}

// update all physical goliath motors
void goliathUpdateMotors() {
  motor_goliath.updateMotor(UPDATE_INTERVAL);
}

// updates all goliath sensors
void goliathUpdateSensors() {
  goliath_angle = encoderGet(enc_goliath);
}

// sets the power of the goliath
void goliathSetPower(int power) {
  motor_goliath.setPower(power);
}

// sets goliath to intake mode
// optionally waits for cone to enter
void goliathIntake(bool wait) {

  // make sure it's spinning the right direction
  goliathSetPower(100);

  // update mode variable
  goliath_mode = GOLIATH_MODE_INTAKE;

  // disable holding
  // if (goliath_mode != GOLIATH_MODE_INTAKE) goliath_holding = false;

  // wait for cone if applicable
  if (wait) {
    while (!goliath_holding) {
      delay(1);
    }
  }
}

// sets goliath to discharge mode
// optionally waits for cone to be spit out
void goliathDischarge(bool wait) {

  // make sure it doesn't think it has a cone
  goliath_holding = false;

  // make sure it's spinning the right direction
  goliathSetPower(-100);

  // update mode variable
  goliath_mode = GOLIATH_MODE_DISCHARGE;

  // wait for discharge if applicable
  if (wait) {
    float target = goliath_angle - GOLIATH_DISCHARGE_ANGLE; // target angle to move past
    int max_time = time + GOLIATH_DISCHARGE_TIMEOUT; // timeout
    while (goliath_angle > target && time < max_time) { // wait to pass target or timeout
      delay(1);
    }
  }
}

// disables the goliath until re-enabled
void goliathDisable() {
 
  // turn off motor
  goliathSetPower(0);
  
  // update state variable
  goliath_mode = GOLIATH_MODE_DISABLED;
}
