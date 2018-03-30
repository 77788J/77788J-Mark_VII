#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "claw.h"
#include "goliath.h"
#include "chainbar.h"

// declare joystick
Joystick joystick;
Joystick joystick_secondary;

// declare lcd
Lcd lcd;

// update all of the registered joysticks
void updateAllJoysticks() {
  joystick.update();
  joystick_secondary.update();
}

// update all of the robot's motors' data
void updateAllMotorData() {
  chassisUpdateMotorData();
  liftUpdateMotorData();
  mogoUpdateMotorData();
  clawUpdateMotorData();
  goliathUpdateMotorData();
  chainbarUpdateMotorData();
}

// update all of the robot's physical motors
void updateAllMotors() {
  chassisUpdateMotors();
  liftUpdateMotors();
  mogoUpdateMotors();
  clawUpdateMotors();
  goliathUpdateMotors();
  chainbarUpdateMotors();
}

// update all of the robot's sensors
void updateAllSensors() {
  chassisUpdateSensors();
  liftUpdateSensors(UPDATE_INTERVAL);
  mogoUpdateSensors();
  clawUpdateSensors();
  goliathUpdateSensors();
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
