#include "lift.h"
#include "math.h"

// init variables to zero
float lift_angle = 0;
float lift_height = 0;
float constant = 0;

// declare motor
Motor motor_lift;

// declare encoder
Encoder enc_lift;

// declare PID
Pid pid_lift;

// inits the lift lifter (motors, pid, etc.)
void liftInit() {

  // define lift encoder
  enc_lift = encoderInit(5, 6, false);

  // update sensors for accurate starting position
  liftUpdateSensors();

  // init motor
  motor_lift.init(MOTOR_LIFT, true, lift_angle);

  // init PID
  pid_lift.init(1.1f, 0, 3.5, LIFT_HEIGHT_MIN, lift_angle);
  pid_lift.target_buffer = 5;

  // calculate lift offset from ground when at 'neutral' position (all bars parallel)
  float rad = lift_angle * 0.0174533f; // convert to radians
  constant = LIFT_HEIGHT_MIN - ((sin(rad) * BEAM_LENGTH) * 2.f); // do the maths
}

// update all lift lifter motors
void liftUpdateMotors() {
  motor_lift.update(lift_angle, UPDATE_INTERVAL);
}

// update all lift lifter sensors
void liftUpdateSensors() {

  // angle (degrees) if the lift
  lift_angle = (encoderGet(enc_lift) * 0.2f) + LIFT_ANGLE_MIN;

  // height (inches) of the lift
  float rad = lift_angle * 0.0174533f; // convert to radians
  lift_height = ((sin(rad) * BEAM_LENGTH) * 2.f) + constant; // translate to height
}

// determines whether or not the lift has reached its target
bool liftAtTarget(bool vel) {
  return pid_lift.atTarget(vel, lift_angle, motor_lift.getVelocity());
}

// sets the power of both lift motors
void liftSetPower(int power) {
  motor_lift.setPower(power, false);
}

void liftGoto(float height, bool wait, bool vel) {

  // update PID target
  pid_lift.setTarget(height);

  // wait if applicable
  if (wait) {
    while (!liftAtTarget(vel)) {
      delay(1);
    }
  }
}
