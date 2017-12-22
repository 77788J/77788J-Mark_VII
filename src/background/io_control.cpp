#include "io_control.h"
#include "chassis.h"

// declare joystick
Joystick joystick;

// update all of the registered joysticks
void updateAllJoysticks() {
  joystick.update();
}

// update all of the robot's motors
void updateAllMotors() {
  chassisUpdateMotors();
}

// update all of the robots sensors
void updateAllSensors() {
  chassisUpdateSensors();
}

// update literally everything
void updateAllIO() {
  updateAllJoysticks();
  updateAllMotors();
  updateAllSensors();
}

// start background task to update everything automatically
void startUpdateTask() {
  taskRunLoop(updateAllIO, UPDATE_INTERVAL);
}
