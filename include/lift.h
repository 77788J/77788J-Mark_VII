#ifndef LIFT_H_
#define LIFT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>
#include <motor.h>
#include <pid.h>

// motor port
#define MOTOR_LIFT 6

// motors
extern Motor motor_lift;

// encoder
extern Encoder enc_lift;

// physical info
#define LIFT_HEIGHT_MAX 45.f
#define LIFT_HEIGHT_MIN 6.0625f
#define LIFT_ANGLE_MIN -27.85f
#define LIFT_ANGLE_MAX 65.87f
#define LIFT_HEIGHT_STATIONARY 18.f
#define BEAM_LENGTH_TOP 13.5f
#define BEAM_LENGTH_BOTTOM 15.f

#define LIFT_SNAP_ENABLED false

// PID
extern bool pid_lift_enabled;
extern Pid pid_lift;

// sensor value will be stored in these variables
extern float lift_angle; // degrees
extern float lift_height; // inches

// inits the lift (PID, motors, etc)
void liftInit();

// update all lift motors
void liftUpdateMotorData();
void liftUpdateMotors();

// updates all lift sensors
void liftUpdateSensors();

// determines whether or not the lift has reached its target
bool liftAtTarget(bool vel);

// returns a recommended timeout for a PID
unsigned int liftGetTimeout(float target);

// low-level lift control
void liftSetPower(int power);

// high level lift control
void liftGoto(float height, bool wait, bool vel);

#ifdef __cplusplus
}
#endif

#endif
