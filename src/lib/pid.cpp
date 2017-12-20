#include "pid.h"
#include "math.h"

Pid :: Pid() {}

// "factory" that initialized a PID
void Pid :: init(float kp_, float ki_, float kd_, float dr_, float target_, float current_) {

  // init tuning parameters
  kp = kp_;
  ki = ki_;
  kd = kd_;
  dr = dr_;

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
}

// target "getter"
float Pid :: getTarget() {
  return target;
}

// integral "getter"
float Pid :: getIntegral() {
  return integral;
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
  float error = current_ - prev;

  // calculate P
  float p = error * kp;

  // calculate I (without newest error data)
  float i = (integral * ki) / dt_;

  // calculate D
  float d;
  if (error == 0)
    d = (kd * (prev_error - error)) / dt_; // don't want to divide by zero
  else
    d = (kd * (prev_error - error) * (dr / error)) / dt_; // implements dynamic derivative algorithm

  // if input is not saturated, integrate
  if (abs(p + i + d) < 100) {
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

  // return the calculated PID output
  return p + i + d;
}
