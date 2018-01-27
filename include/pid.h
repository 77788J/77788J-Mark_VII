#ifndef PID_H_
#define PID_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>

class Pid {

public:

  // tuning parameters
  float kp;
  float ki;
  float kd;
  float kp_rev;
  float ki_rev;
  float kd_rev;

  // maximum outputs
  float max_p;
  float max_i;
  float max_d;

  float i_factor;

  // buffer around target to safely assume the system is close enough
  float target_buffer;

  // buffer around velocity to safely assume it is ~0
  float velocity_buffer;

  // default initializer
  // MAKE SURE TO FULLY INITIALIZE WITH <Pid>.init()
  Pid();

  // actually initializes the PID
  void init(float kp_, float ki_, float kd_, float target_, float current_);

  // gets the current target of the PID
  float getTarget();

  // gets the current integral value of the PID
  float getIntegral();

  // determines whether or not the system is at the target (within a margin of error)
  bool atTarget(bool , float current_, float velocity_);

  // sets the integral component to a specified value
  void setIntegral(float integral_);

  // resets the integral component to zero
  void resetIntegral();

  // change the target of the PID
  void setTarget(float target_);

  // runs one iteration of the PID
  float run(float current_, float dt_);

private:

  // previous position and error
  float prev;
  float prev_error;

  // logs whether or not the PID is at the target stage
  bool at_target;
  bool at_target_vel; // accounts for velocity as well as position

  // accumulated integral value
  float integral;

  // target state of PID
  float target;

};

#ifdef __cplusplus
}
#endif

#endif
