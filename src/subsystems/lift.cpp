#include "lift.h"
#include "math.h"

// init variables to zero
float lift_angle = 0;
float lift_height = 0;
float lift_height_prev = 0;
float lift_speed = 0;
static float constant = 0;
bool pid_lift_enabled = true;

// declare motor
Motor motor_lift;

// declare encoder
Encoder enc_lift;

// declare PID
Pid pid_lift;

// inits the lift lifter (motors, pid, etc.)
void liftInit() {

  // define lift encoder
  enc_lift = encoderInit(5, 6, true);

  // update sensors for accurate starting position
  liftUpdateSensors(1);
  liftUpdateSensors(1);

  // init motor
  motor_lift.init(MOTOR_LIFT, true, lift_angle);
  motor_lift.slew = true;
  motor_lift.slew_rate = .5f;

  // init PID
  pid_lift.init(10.f, 5.f, 1200.f, LIFT_HEIGHT_MIN, lift_angle);
  pid_lift.target_buffer = .2f;
  pid_lift.max_i = 70.f;
  pid_lift.max_d = 200.f;
  pid_lift.i_factor = .001f;

  // calculate lift offset from ground when at 'neutral' position (all bars parallel)
  float rad = lift_angle * .01745329251f; // convert to radians
  constant = -(-LIFT_HEIGHT_MIN + (sin(rad) * BEAM_LENGTH_BOTTOM) + (sin(rad) * BEAM_LENGTH_TOP)); // do the maths
}

// update all lift lifter motors
void liftUpdateMotorData() {
  motor_lift.updateData(lift_angle, UPDATE_INTERVAL);
}

// update all lift lifter motors
void liftUpdateMotors() {
  motor_lift.updateMotor(UPDATE_INTERVAL);
}

// update all lift lifter sensors
void liftUpdateSensors(int dt) {

  // angle (degrees) if the lift
  lift_angle = (.142857143f * encoderGet(enc_lift)) + LIFT_ANGLE_MIN;

  // height (inches) of the lift
  float rad = lift_angle * 0.0174533f; // convert to radians
  lift_height = (sin(rad) * BEAM_LENGTH_BOTTOM) + (sin(rad) * BEAM_LENGTH_TOP) + constant; // translate to height

  lift_speed = (lift_speed * .4f + (lift_height - lift_height_prev) * .6f) * (1000 / dt);

  lift_height_prev = lift_height;
}

// determines whether or not the lift has reached its target
bool liftAtTarget(bool vel) {
  return pid_lift.atTarget(vel, lift_angle, motor_lift.getVelocity());
}

// returns a recommended timeout for a PID
unsigned int liftGetTimeout(float target) {
  float delta = target - lift_height;
  return abs(delta * 69.420f);
}

// sets the power of both lift motors
void liftSetPower(int power) {
  motor_lift.setPower(power);
}

void liftGoto(float height, bool wait, bool vel) {

  // setup timeout
  unsigned int timeout = 0;
  unsigned int max_timeout = liftGetTimeout(pid_lift.getTarget());

  // update PID target
  pid_lift.setTarget(height);

  // wait if applicable
  if (wait) {
    while (!liftAtTarget(vel) && timeout < max_timeout) {
      delay(1);
      timeout += 1;
    }
  }
}
