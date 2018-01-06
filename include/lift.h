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
extern Motor motor_lift_r;

// encoder
extern Encoder enc_lift;

// physical info
#define LIFT_HEIGHT_MAX 52.f
#define LIFT_HEIGHT_MIN -10.f
#define LIFT_ANGLE_MIN -5.f
#define LIFT_ANGLE_MAX 45.f
#define BEAM_LENGTH 16.f

// PID
extern Pid pid_lift;

// sensor value will be stored in these variables
extern float lift_angle; // degrees
extern float lift_height; // inches

// inits the lift (PID, motors, etc)
void liftInit();

// update all lift motors
void liftUpdateMotors();

// updates all lift sensors
void liftUpdateSensors();

// low-level lift control
void liftSetPower(int power);

// high level lift control
void liftGoto(float height, bool wait, bool vel);

#ifdef __cplusplus
}
#endif

#endif
