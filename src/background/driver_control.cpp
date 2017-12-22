#include "main.h"
#include "chassis.h"
#include "button_manager.h"
#include "math.h"

// driver control enabled?
bool driver_chassis = true;
bool driver_mogo = true;

// time when last updated
int updated = 0;

// chassis control
void driverControlChassis() {
  int l = joystick.analogLH;
  int r = joystick.analogRH;

  if (abs(l) < 20) l = 0;
  if (abs(r) < 20) r = 0;

  if ((l >= 0) != (r >= 0)) {
    l *= .75f;
    r *= .75f;
  }

  chassisSetPowerExt(l, r);
}

// full driver control
void driverControl() {
  waitForJoystickUpdate(joystick, updated);

  if (driver_chassis) {
    driverControlChassis();
  }

  updated += UPDATE_INTERVAL;
}

// start driver control task
void driverControlStart() {
  updated = 0;
  taskRunLoop(driverControl, UPDATE_INTERVAL);
}
