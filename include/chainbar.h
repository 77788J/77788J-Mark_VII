#ifndef CHAINBAR_H_
#define CHAINBAR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>
#include <motor.h>
#include <pid.h>

// motor port
#define MOTOR_CHAINBAR 8

// motors
extern Motor motor_chainbar;

// analog sensors
#define POT_CHAINBAR 5

// physical info
#define CHAINBAR_RETRACTED 105.f
#define CHAINBAR_STACK 87.676f
#define CHAINBAR_GRAB -23.f

// PID
extern Pid pid_chainbar;

// sensor values (scaled)
extern float chainbar_angle; // degrees

// inits the chainbar (PID, motors, etc)
void chainbarInit();

// update all chainbar motors
void chainbarUpdateMotorData();
void chainbarUpdateMotors();

// updates all chainbar sensors
void chainbarUpdateSensors();

// determines whether or not the chainbar has reached its target
bool chainbarAtTarget(bool vel);

// returns a recommended timeout for a PID
unsigned int chainbarGetTimeout(float target);

// low-level chainbar control
void chainbarSetPower(int power);

// high level chainbar control
void chainbarGoto(float angle, bool wait, bool vel);

#ifdef __cplusplus
}
#endif

#endif
