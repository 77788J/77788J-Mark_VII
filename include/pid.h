#ifndef PID_H_
#define PID_H_

#include <main.h>

class Pid {

public:

  // tuning parameters
  float kp;
  float ki;
  float kd;
  float dr;

  // default initializer
  // MAKE SURE TO FULLY INITIALIZE WITH <Pid>.init()
  Pid();

  // actually initializes the PID
  void init(float kp_, float ki_, float kd_, float dr_, float target_, float current_);

  // gets the current target of the PID
  float getTarget();

  // gets the current integral value of the PID
  float getIntegral();

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

  // accumulated integral value
  float integral;

  // target state of PID
  float target;

};

#endif
