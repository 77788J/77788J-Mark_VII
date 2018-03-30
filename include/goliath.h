#ifndef GOLIATH_H_
#define GOLIATH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>
#include <motor.h>
#include <pid.h>

// motor port
#define MOTOR_GOLIATH 9

// min degrees for goliath to spin to discharge a cone
#define GOLIATH_DISCHARGE_ANGLE 110

// timeout for discharge (in ms)
#define GOLIATH_DISCHARGE_TIMEOUT 500

// goliath modes
#define GOLIATH_MODE_DISABLED 0
#define GOLIATH_MODE_INTAKE 1
#define GOLIATH_MODE_DISCHARGE 2

// motors
extern Motor motor_goliath;

// encoder
extern Encoder enc_goliath;

// PID
extern Pid pid_goliath;

extern float goliath_angle;

// variables
extern unsigned char goliath_mode;

extern int goliath_timeout;
extern bool goliath_holding; // is it currently holding a cone?
extern bool goliath_spinning; // logs whether or not it is spinning

// inits the goliath (PID, motors, etc)
void goliathInit();

// update all goliath motors
void goliathUpdateMotorData();
void goliathUpdateMotors();

// updates all goliath sensors
void goliathUpdateSensors();

// sets the power of the goliath
void goliathSetPower(int power);

// sets goliath to intake mode
// optionally waits for cone to enter
void goliathIntake(bool wait);

// sets goliath to discharge mode
// optionally waits for cone to be spit out
void goliathDischarge(bool wait);

// disables the goliath
void goliathDisable();

#ifdef __cplusplus
}
#endif

#endif
