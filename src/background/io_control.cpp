#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "claw.h"
#include "chainbar.h"

// declare joystick
Joystick joystick;

// declare lcd
Lcd lcd;

// update all of the registered joysticks
void updateAllJoysticks() {
  joystick.update();
}

// update all of the robot's motors' data
void updateAllMotorData() {
  chassisUpdateMotorData();
  liftUpdateMotorData();
  mogoUpdateMotorData();
  clawUpdateMotorData();
  chainbarUpdateMotorData();
}

// update all of the robot's physical motors
void updateAllMotors() {
  chassisUpdateMotors();
  liftUpdateMotors();
  mogoUpdateMotors();
  clawUpdateMotors();
  chainbarUpdateMotors();
}

// update all of the robot's sensors
void updateAllSensors() {
  chassisUpdateSensors();
  liftUpdateSensors();
  mogoUpdateSensors();
  clawUpdateSensors();
  chainbarUpdateSensors();
}

// update all of the robot's LCDs
void updateAllLcds() {
  lcd.updateButtons();
}

// update literally everything
void updateAllIO() {
  updateAllJoysticks();
  updateAllMotors();
  updateAllSensors();
  updateAllLcds();
}

// start background task to update everything automatically
void startUpdateIOTask() {
  taskRunLoop(updateAllIO, UPDATE_INTERVAL);
}
