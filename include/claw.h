#ifndef CLAW_H_
#define CLAW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>
#include <motor.h>
#include <pid.h>

// motor port
#define MOTOR_CLAW 9

// motors
extern Motor motor_claw;

// analog sensors
#define POT_CLAW 2

// physical info
#define CLAW_OPEN 170.f
#define CLAW_CLOSED 90.f

// PID
extern Pid pid_claw;

// sensor values (scaled)
extern float claw_angle; // degrees

// inits the claw (PID, motors, etc)
void clawInit();

// update all claw motors
void clawUpdateMotorData();
void clawUpdateMotors();

// updates all claw sensors
void clawUpdateSensors();

// determines whether or not the claw has reached its target
bool clawAtTarget(bool vel);

// returns a recommended timeout for a PID
unsigned int clawGetTimeout(float target);

// low-level claw control
void clawSetPower(int power);

// high level claw control
void clawGoto(float angle, bool wait, bool vel);

#ifdef __cplusplus
}
#endif

#endif
