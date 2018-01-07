#ifndef MOGO_H_
#define MOGO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>
#include <motor.h>
#include <pid.h>

// motor port
#define MOTOR_MOGO 3

// motors
extern Motor motor_mogo;

// sensors
#define POT_MOGO_L 1
#define POT_MOGO_R 2

// angle presets
#define MOGO_ANGLE_EXTENDED 200
#define MOGO_ANGLE_GRAB 100
#define MOGO_ANGLE_RETRACTED 0

// PID
extern Pid pid_mogo;

// sensor values will be stored in these variables
extern float mogo_angle_l;
extern float mogo_angle_r;
extern float mogo_angle;

// inits the mogo lifter (PID, motors, etc)
void mogoInit();

// update all mogo motors
void mogoUpdateMotors();

// updates all mogo sensors
void mogoUpdateSensors();

// determines whether or not the mogo lifter has reached its target
bool mogoAtTarget(bool vel);

// low-level mogo control
void mogoSetPower(int power);

// high level mogo control
void mogoGoto(float angle, bool wait, bool vel);

#ifdef __cplusplus
}
#endif

#endif
