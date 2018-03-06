#include "main.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "claw.h"
#include "goliath.h"
#include "chainbar.h"
#include "io_control.h"
#include "driver_control.h"
#include "recorder.h"
#include "macros.h"
#include "math.h"

// driver control enabled?
bool driver_chassis = true;
bool driver_lift = true;
bool driver_mogo = true;
bool driver_claw = true;
bool driver_goliath = true;
bool driver_chainbar = true;

// has it stopped yet?
bool is_stopped = false;

// chassis control
void driverControlChassis() {

  // store joystick output in mutable variables
  int l = joystick.analogLV;
  if (fabs(joystick_secondary.analogLV) > fabs(l))
    l = joystick_secondary.analogLV;

  int r = joystick.analogRV;
  if (fabs(joystick_secondary.analogRV) >
    fabs(r)) r = joystick_secondary.analogRV;

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
void driverControlLift() {

  pid_lift_enabled = false;

  if (pid_lift_enabled) {

    // raise button
    if (joystick.btn5U || joystick_secondary.btn5U) {
      pid_lift.setTarget(LIFT_HEIGHT_MAX);
    }

    // lower button
    else if (joystick.btn5D || joystick_secondary.btn5D) {
      pid_lift.setTarget(LIFT_HEIGHT_MIN);
    }

    // if either were both just released and neither are pressed, set the power to 0
    else if (joystick.btn5U_new + joystick.btn5D_new < 0 || joystick_secondary.btn5U_new + joystick_secondary.btn5D_new < 0) {

      // if the lift should snap to the nearest cone height, snap
      if (LIFT_SNAP_ENABLED) {

          if (joystick.btn5U_new == -1 || joystick_secondary.btn5U_new == -1) {
            pid_lift.setTarget((ceil(lift_height / 2.8f) * 2.8f) + 1.f); // round up
            if (fabs(lift_height - pid_lift.getTarget()) < 1.2f) pid_lift.setTarget(pid_lift.getTarget() + 2.8f); // see if it's too close and raise if so
            if (lift_height < 8.f) pid_lift.setTarget(10.f); // min height to stack
            if (pid_lift.getTarget() > LIFT_HEIGHT_MAX) pid_lift.setTarget(LIFT_HEIGHT_MAX); // make sure it doesn't go too tall
          }
          if (joystick.btn5D_new == -1 || joystick_secondary.btn5D_new == -1) {
            pid_lift.setTarget((floor(lift_height / 2.8f) * 2.8f) + 1.f); // round down
            if (fabs(lift_height - pid_lift.getTarget()) < 1.2f) pid_lift.setTarget(pid_lift.getTarget() - 2.8f); // see if it's too close and lower if so
            if (lift_height < 8.f) pid_lift.setTarget(LIFT_HEIGHT_MIN); // just lower it all the way
            if (pid_lift.getTarget() > LIFT_HEIGHT_MAX) pid_lift.setTarget(LIFT_HEIGHT_MAX); // make sure it doesn't go too tall
          }
      }

      // if snap is disabled, just stop the lift where it is
      else pid_lift.setTarget(lift_height);
    }
  }

  else {

    if (joystick.btn5U || joystick_secondary.btn5U) liftSetPower(100);
    else if (joystick.btn5D || joystick_secondary.btn5D) liftSetPower(-100);
    else liftSetPower(0);

  }
}

// claw control
void driverControlClaw() {
  if (joystick.btn6U) pid_claw.setTarget(CLAW_CLOSED);
  if (joystick.btn6D) pid_claw.setTarget(CLAW_OPEN);
}

// goliath control
void driverControlGoliath() {
  if (joystick.btn6D || joystick_secondary.btn6D) goliathDischarge(false);
  else if (joystick.btn6U_new == 1 || joystick_secondary.btn6U_new == 1) {
    if (goliath_mode == GOLIATH_MODE_DISABLED) {
      goliath_timeout = -1;
      goliath_holding = false;
      goliathIntake(false);
    }
    else goliathDisable();
  }
  else if (goliath_mode == GOLIATH_MODE_DISCHARGE && !goliath_holding) goliathIntake(false);
}

// mogo lifter control
void driverControlMogo() {

  // extend button
  if (joystick.btn8U || joystick_secondary.btn8U) {
    pid_mogo_enabled = false;
    pid_mogo.setTarget(MOGO_ANGLE_EXTENDED);
    mogoSetPower(100);
  }

  // retract button
  else if (joystick.btn8D || joystick_secondary.btn8D) {
    pid_mogo_enabled = false;
    pid_mogo.setTarget(MOGO_ANGLE_RETRACTED);
    mogoSetPower(-100);
  }

  else {
    pid_mogo_enabled = true;
  }

  // if mogo lifter was being extended/retracted and is not past grab point
  if (((joystick.btn8U_new == -1 || joystick_secondary.btn8U_new == -1) && mogo_angle + 15 < MOGO_ANGLE_GRAB) ||
      ((joystick.btn8D_new == -1 || joystick_secondary.btn8D_new == -1) && mogo_angle - 15 > MOGO_ANGLE_GRAB)) {

    // set mogo target to grab
    pid_mogo.setTarget(MOGO_ANGLE_GRAB);
  }
}

// chainbar control
void driverControlChainbar() {
  if (joystick.btn7U || joystick_secondary.btn7U || joystick_secondary.btn8U) {
    if (chainbar_angle < CHAINBAR_STACK - 15.f) pid_chainbar.setTarget(CHAINBAR_STACK);
    else pid_chainbar.setTarget(CHAINBAR_RETRACTED);
  }
  if (joystick.btn7D || joystick_secondary.btn7D || joystick_secondary.btn8D) {
    if (chainbar_angle > CHAINBAR_STACK + 15.f) pid_chainbar.setTarget(CHAINBAR_STACK);
    else pid_chainbar.setTarget(CHAINBAR_GRAB);
  }
}

// check if macro should be interrupted
void driverInterrupt() {

  if (((joystick.btn5U || joystick.btn5D || joystick_secondary.btn5U || joystick_secondary.btn5D) && !driver_lift) ||
  ((joystick.btn6D || joystick_secondary.btn6D) && !driver_goliath) ||
  ((joystick.btn7U || joystick.btn7D || joystick_secondary.btn7U || joystick_secondary.btn7D) && !driver_chainbar) ||
  ((joystick.btn8U || joystick.btn8D) && !driver_mogo)) stopMacro();

}

// full driver control
unsigned char mode = CHASSIS_MODE_POSITION;
void updateDriverControl() {

  driverInterrupt();

  // if 'recording' for auto
  if (RECORDING_ENABLED) {

    // make sure that the chassis is in the right mode and move
    if (abs(joystick.analogLV) > 20) { // translation
      if (mode != CHASSIS_MODE_POSITION) logState(mode); // if the mode is switching, log the state
      mode = CHASSIS_MODE_POSITION; // update the new mode
      chassisSetPower(joystick.analogLV); // move the chassis
    }
    else if (abs(joystick.analogRH) > 20) { // rotation
      if (mode != CHASSIS_MODE_ANGLE) logState(mode); // if the mode is switching, log the state
      mode = CHASSIS_MODE_ANGLE; // update the new mode
      chassisSetPowerExt(joystick.analogRH, -joystick.analogRH); // rotate the chassis
    }
    else chassisSetPower(0); // stopped

    // lift control
    driverControlLift();

    // mogo control
    driverControlMogo();

    // claw control
    driverControlClaw();

    // chainbar control
    driverControlChainbar();

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

    // run claw control
    if (driver_claw) {
      // driverControlClaw();
    }

    // run goliath control
    if (driver_goliath) {
      driverControlGoliath();
    }

    // run lift control
    if (driver_lift) {
      driverControlLift();
    }

    // run chainbar control
    if (driver_chainbar) {
      driverControlChainbar();
    }
  }
}
