#ifndef IO_CONTROL_H_
#define IO_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>
#include <joystick.h>

// declare joystick
extern Joystick joystick;

// updates all of the registered joysticks
void updateAllJoysticks();

// update all of the robot's motors
void updateAllMotors();

// update all of the robots sensors
void updateAllSensors();

// update literally everything
void updateAllIO();

// start background task to update everything automatically
void startUpdateIOTask();

#ifdef __cplusplus
}
#endif

#endif
