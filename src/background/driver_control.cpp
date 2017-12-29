#include "main.h"
#include "chassis.h"
#include "mogo.h"
#include "io_control.h"
#include "driver_control.h"
#include "math.h"

// driver control enabled?
bool driver_chassis = true;
bool driver_mogo = true;

// was moving previously?
bool was_moving = false;

// has it stopped yet?
bool is_stopped = false;

// chassis control
void driverControlChassis() {

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

  // if joysticks are both ~0...
  if (l == 0 && r == 0) {

    // if the velocity is ~0 AND the it hasn't been in the past...
    if (chassis_mode == CHASSIS_MODE_DIRECT &&
        abs(motor_chassis_fl.getVelocity()) <= 0.01f &&
        abs(motor_chassis_fr.getVelocity()) <= 0.01f &&
        !is_stopped) {

      // activate PID
      chassis_mode = CHASSIS_MODE_POSITION;
      pid_chassis_l.setTarget(chassis_left);
      pid_chassis_r.setTarget(chassis_right);

      // log that the chassis has now officially stopped
      is_stopped = true;
    }

    // log that the chassis is not stop being controlled
    was_moving = false;
  }

  // otherwise set the chassis power to the processed joystick output
  else {
    chassis_mode = CHASSIS_MODE_DIRECT;
    chassisSetPowerExt(l, r);
    was_moving = true;
    is_stopped = false;
  }
}

// mogo lifter control
void driverControlMogo() {

  // extend button
  if (joystick.btn6U) {
    pid_mogo.setTarget(MOGO_ANGLE_EXTENDED);
  }

  // retract button
  else if (joystick.btn6D) {
    pid_mogo.setTarget(MOGO_ANGLE_RETRACTED);
  }

  // if mogo lifter was being extended/retracted and is not past grab point
  if ((joystick.btn6U_new == -1 && mogo_angle < MOGO_ANGLE_GRAB) ||
      (joystick.btn6D_new == -1 && mogo_angle > MOGO_ANGLE_GRAB)) {

    // set mogo target to grab
    pid_mogo.setTarget(MOGO_ANGLE_GRAB);
  }
}

// full driver control
void updateDriverControl() {

  // run chassis control
  if (driver_chassis) {
    driverControlChassis();
  }

  // run mogo control
  if (driver_mogo) {
    driverControlMogo();
  }
}
