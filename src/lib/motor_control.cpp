#include "motor_control.h"
#include "button_manager.h"
#include "chassis.h"

int updated = 0;

void updateAllMotors() {
  waitForJoystickUpdate(joystick, updated);

  chassisUpdateMotors();

  updated += UPDATE_INTERVAL;
}

void startMotorTask() {
  updated = 0;
  taskRunLoop(updateAllMotors, UPDATE_INTERVAL);
}
