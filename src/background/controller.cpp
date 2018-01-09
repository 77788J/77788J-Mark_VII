#include "controller.h"
#include "io_control.h"
#include "driver_control.h"
#include "pid_control.h"
#include "chassis.h"
#include "claw.h"
#include "mogo.h"

// update literally everything on the bot
void updateAll() {

  // update joystick inputs
  updateAllJoysticks();

  // update sensor inputs
  updateAllSensors();

  // update motors (for velocity)
  updateAllMotors();

  // run driver control (if in driver control mode)
  if (isEnabled() && !isAutonomous()) updateDriverControl();

  // update PIDs
  updateAllPids();

  // update motors (for physical motor output)
  updateAllMotors();

  updateAllLcds();

  if (lcd.btn_l_new == 1) lcd.setText(0, "LEFT");
  if (lcd.btn_m_new == 1) lcd.setText(0, "MIDDLE");
  if (lcd.btn_r_new == 1) lcd.setText(0, "RIGHT");
}

// starts a background task with the controller in it
void startController() {
  taskRunLoop(updateAll, UPDATE_INTERVAL);
}
