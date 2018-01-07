#include "main.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "io_control.h"
#include "driver_control.h"
#include "recorder.h"
#include "math.h"

// driver control enabled?
bool driver_chassis = true;
bool driver_lift = true;
bool driver_mogo = true;

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

  // if joysticks are close to 100, treat them as 100
  if (abs(l) > 90) l = 100 * sign(l);
  if (abs(r) > 90) r = 100 * sign(r);

  // // if the joystick are facing opposite directions, slow them down
  // // for more accurate turning
  // if ((l >= 40) != (r >= 40) && (l <= -40) != (r <= -40)) {
  //   l *= .75f;
  //   r *= .75f;
  // }

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

    else {
      chassisSetPower(0);
    }
  }

  // otherwise set the chassis power to the processed joystick output
  else {
    chassis_mode = CHASSIS_MODE_DIRECT;
    chassisSetPowerExt(l, r);
    is_stopped = false;
  }
}

// lift control
bool lift_stopped = false;
void driverControlLift() {

  // raise button
  if (joystick.btn5U) {
    pid_lift.setTarget(LIFT_HEIGHT_MAX);
    lift_stopped = false;
  }

  // lower button
  else if (joystick.btn5D) {
    pid_lift.setTarget(LIFT_HEIGHT_MIN);
    lift_stopped = false;
  }

  // if either were both just released and neither are pressed, set the power to 0
  else if (joystick.btn5U + joystick.btn5D < 0) {
    motor_lift.setPower(0, false);
  }

  // otherwise wait until the velocity is ~0 and start the PID
  else if (!lift_stopped && motor_lift.getVelocity() <= .01f) {
    pid_lift.setTarget(lift_height);
    lift_stopped = true;
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
  if ((joystick.btn6U_new == -1 && mogo_angle + 15 < MOGO_ANGLE_GRAB) ||
      (joystick.btn6D_new == -1 && mogo_angle - 15 > MOGO_ANGLE_GRAB)) {

    // set mogo target to grab
    pid_mogo.setTarget(MOGO_ANGLE_GRAB);
  }
}

// full driver control
unsigned char mode = CHASSIS_MODE_POSITION;
void updateDriverControl() {

  // if 'recording' for auto
  if (RECORDING_ENABLED) {

    // make sure that the chassis is in the right mode and move
    if (abs(joystick.analogLV) > 20) {
      if (mode != CHASSIS_MODE_POSITION) logState(mode); // if the mode is switching, log the state
      mode = CHASSIS_MODE_POSITION; // update the new mode
      chassisSetPower(joystick.analogLV); // move the chassis
    }
    if (abs(joystick.analogRH) > 20) {
      if (mode != CHASSIS_MODE_ANGLE) logState(mode); // if the mode is switching, log the state
      mode = CHASSIS_MODE_ANGLE; // update the new mode
      chassisSetPowerExt(joystick.analogRH, -joystick.analogRH); // rotate the chassis
    }

    // lift control
    driverControlLift();

    // mogo control
    driverControlMogo();

    // log state if log button is released
    if (joystick.btn7U_new == -1) logState(mode);
  }

  else {

    // run chassis control
    if (driver_chassis) {
      driverControlChassis();
    }

    // run mogo control
    if (driver_mogo) {
      driverControlMogo();
    }

    // run lift control
    if (driver_lift) {
      driverControlLift();
    }
  }
}
