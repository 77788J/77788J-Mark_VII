#include "main.h"
#include "chassis.h"
#include "io_control.h"
#include "math.h"

// driver control enabled?
bool driver_chassis = true;
bool driver_mogo = true;

// chassis control
void driverControlChassis() {

  // make sure chassis is in direct control mode
  chassis_mode = CHASSIS_MODE_DIRECT;

  // store joystick output (scaled between -100 to 100) in mutable variables
  int l = (float) joystick.analogLH * 0.787401575f;
  int r = (float) joystick.analogRH * 0.787401575f;

  // if joysticks are close enough to zero, treat them as zero
  if (abs(l) < 10) l = 0;
  if (abs(r) < 10) r = 0;

  // if the joystick are facing opposite directions, slow them down
  // for more accurate turning
  if ((l >= 0) != (r >= 0)) {
    l *= .75f;
    r *= .75f;
  }

  // set the chassis power to the processed joystick output
  chassisSetPowerExt(l, r);
}

// full driver control
void updateDriverControl() {

  // run chassis control
  if (driver_chassis) {
    driverControlChassis();
  }
}
