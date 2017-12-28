#include "io_control.h"
#include "chassis.h"
#include "mogo.h"

// declare joystick
Joystick joystick;

// update all of the registered joysticks
void updateAllJoysticks() {
  joystick.update();
}

// update all of the robot's motors
void updateAllMotors() {
  chassisUpdateMotors();
  mogoUpdateMotors();
}

// update all of the robots sensors
void updateAllSensors() {
  chassisUpdateSensors();
  mogoUpdateSensors();
}

// update literally everything
void updateAllIO() {
  updateAllJoysticks();
  updateAllMotors();
  updateAllSensors();
}

// start background task to update everything automatically
void startUpdateIOTask() {
  taskRunLoop(updateAllIO, UPDATE_INTERVAL);
}
