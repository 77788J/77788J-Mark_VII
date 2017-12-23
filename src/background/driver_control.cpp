#include "main.h"
#include "chassis.h"
#include "io_control.h"
#include "driver_control.h"
#include "math.h"

// driver control enabled?
bool driver_chassis = true;
bool driver_mogo = true;

// was moving previously?
bool was_moving = false;

// chassis control
void driverControlChassis() {

  // make sure chassis is in direct control mode
  chassis_mode = CHASSIS_MODE_DIRECT;

  // store joystick output in mutable variables
  int l = joystick.analogLV;
  int r = joystick.analogRV;

  // if joysticks are close enough to zero, treat them as zero
  if (abs(l) < 20) l = 0;
  if (abs(r) < 20) r = 0;

  // if the joystick are facing opposite directions, slow them down
  // for more accurate turning
  if ((l >= 0) != (r >= 0)) {
    l *= .75f;
    r *= .75f;
  }

  chassisSetPower(0);

  // if the robot should be stopped, activate PID to keep position
  if (l == 0 && r == 0) {

    // update targets only if the chassis was moving the previous run
    if (motor_chassis_fl.getVelocity() == 0 && motor_chassis_fr.getVelocity() == 0) {
      chassis_mode = CHASSIS_MODE_POSITION;
      pid_chassis_l.setTarget(chassis_left);
      pid_chassis_r.setTarget(chassis_right);
    }

    was_moving = false;
  }

  // otherwise set the chassis power to the processed joystick output
  else {
    chassis_mode = CHASSIS_MODE_DIRECT;
    chassisSetPowerExt(l, r);
    was_moving = true;
  }
}

// full driver control
void updateDriverControl() {

  // run chassis control
  if (driver_chassis) {
    driverControlChassis();
  }
}
