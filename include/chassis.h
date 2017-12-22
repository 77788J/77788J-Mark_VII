#ifndef CHASSIS_H_
#define CHASSIS_H_

#include <main.h>

// motors
#define MOTOR_CHASSIS_FL 5
#define MOTOR_CHASSIS_BL 2
#define MOTOR_CHASSIS_FR 6
#define MOTOR_CHASSIS_BR 9

// sensors
extern Encoder enc_chassis_l;
extern Encoder enc_chassis_r;

// sensor values will be stored in these variables
extern float chassis_left;
extern float chassis_right;
extern float chassis_angle;

// inits the chassis (PID, encoders, etc)
void chassisInit();

// update all chassis motors
void chassisUpdateMotors();

// updates all chassis sensors
void chassisUpdateSensors();

// low-level motor control
void chassisSetPowerL(int power);
void chassisSetPowerR(int power);

// mid-level motor control
void chassisSetPower(int power);
void chassisSetPowerExt(int l, int r);

// high level motor control
void chassisMove(float l, float r);
void chassisRotate(float degrees);

#endif
