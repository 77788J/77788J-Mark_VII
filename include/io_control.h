#ifndef IO_CONTROL_H_
#define IO_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>
#include <joystick.h>
#include <lcd.h>

// declare joystick
extern Joystick joystick;
extern Joystick joystick_secondary;

// declare LCD
extern Lcd lcd;

// updates all of the registered joysticks
void updateAllJoysticks();

// update all of the robot's motors' data
void updateAllMotorData();

// update all of the robot's physical motors
void updateAllMotors();

// update all of the robot's sensors
void updateAllSensors();

// updates all of the robot's LCDs
void updateAllLcds();

// update literally everything
void updateAllIO();

// start background task to update everything automatically
void startUpdateIOTask();

#ifdef __cplusplus
}
#endif

#endif
