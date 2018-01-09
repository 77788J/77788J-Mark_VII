#include "pid.h"
#include "math.h"

Pid :: Pid() {}

// "factory" that initialized a PID
void Pid :: init(float kp_, float ki_, float kd_, float target_, float current_) {

  // init tuning parameters
  kp = kp_;
  ki = ki_;
  kd = kd_;
  target_buffer = 1.2f;
  velocity_buffer = 3;

  // init maximum output of each component
  max_p = 200;
  max_i = 50;
  max_d = 64;

  // init target
  target = target_;

  // init "previous" state
  prev = current_;

  // init previous error and integral to 0
  prev_error = 0;
  integral = 0;

  // PID starts off not at target (false until proven true)
  at_target = false;
  at_target_vel = false;
}

// target "getter"
float Pid :: getTarget() {
  return target;
}

// integral "getter"
float Pid :: getIntegral() {
  return integral;
}

// returns whether or not the PID system is approx. at its target
// can optionally factor in velocity
bool Pid :: atTarget(bool v, float current_, float velocity_) {

  // update at_target variables
  if (abs(target - current_) <= target_buffer) {
    at_target = true;
    at_target_vel = (abs(velocity_) <= velocity_buffer);
  }
  else  {
    at_target = false;
    at_target_vel = false;
  }

  // return correct value
  if (v) return at_target_vel;
  else return at_target;
}

// sets the integral accumulator to a specified value
void Pid :: setIntegral(float integral_) {
  integral = integral_;
}

// resets the integral accumulator to zero
void Pid :: resetIntegral() {
  integral = 0;
}

// changes the target value and "resets" the PID
void Pid :: setTarget(float target_) {
  resetIntegral();
  prev_error = 0;
  target = target_;
}

// runs one iteration of the PID control loop
float Pid :: run(float current_, float dt_) {

  // calculate error
  float error = target - current_;

  // calculate P
  float p = error * kp;

  // calculate I (without newest error data)
  float i = (integral * ki) / dt_;

  // calculate D
  float d = (kd * (error - prev_error)) / dt_;

  // if input is not saturated, integrate
  if (abs(p + d) < 20 && ((error < 20) || abs(error - prev_error) < (.006f * dt_))) {
    integral += error;
  }

  // update I to reflect newest data (will do nothing if input is saturated)
  i = (integral * ki) / dt_;

  // update previous values for next run
  prev = current_;
  prev_error = error;

  // confine P, I, and D components to within their set bounds
  p = limit(p, -max_p, max_p);
  i = limit(i, -max_i, max_i);
  d = limit(d, -max_d, max_d);

  // determine whether or not the system is "at" the target
  if (abs(target - current_) <= target_buffer) {
    at_target = true;
    at_target_vel = (abs(calcRpm(current_ - prev, UPDATE_INTERVAL)) <= velocity_buffer);
  }
  else {
    at_target = false;
    at_target_vel = false;
  }

  // return the calculated PID output
  int result = p + i + d;
  return result;
}
