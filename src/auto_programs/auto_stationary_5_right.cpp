#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "chainbar.h"
#include "lift.h"
#include "mogo.h"
#include "goliath.h"
#include "math.h"


void autoRunRightStationary5() {

  // set gyro scaling correct
  // gyro

  // raise lift and extend chainbar
  mogoGoto(MOGO_ANGLE_EXTENDED, false, false);
  liftGoto(LIFT_HEIGHT_STATIONARY + 2.f, true, true);

  // move to stationary goal
  chassisMove(22.5f, 22.5f, true, true);
  delay(200);

  // lower lift slightly and open claw
  liftGoto(LIFT_HEIGHT_STATIONARY - 4.f, true, true);
  delay(300);

  // discharge and raise lift
  goliathDischarge(false);
  liftGoto(LIFT_HEIGHT_STATIONARY + 2.f, true, false);
  delay(100);

  // back up and retract chainbar
  chainbarGoto(CHAINBAR_RETRACTED, false, false);
  chassisMove(-21.391f, -21.391f, true, true);

  // lower lift, lower mogo, and rotate
  liftGoto(LIFT_HEIGHT_MIN, false, false);
  mogoGoto(MOGO_ANGLE_GRAB, false, false);
  chassisRotate(96.f, true, true);

  float b = pid_chassis_theta.target_buffer;
  pid_chassis_theta.target_buffer = 2.f;

  chassisResetSensors();
  delay(250);

  // move to mogo
  chassisMove(50.81f, 50.81f, true, true);

  // intake mogo
  mogoGoto(MOGO_ANGLE_EXTENDED, true, false);
  delay(750);

  if (auto_cone) {

    // make sure lift is pressed down
    pid_lift_enabled = false;
    liftSetPower(-30);

  // begin to lower chainbar for cone
  chainbarGoto(CHAINBAR_GRAB, false, false);

    // switch goliath to intake mode
    goliath_timeout = -1;
    goliathIntake(false);

    // move backwards a bit
    chassisMove(-6.f, -6.f, true, false);

    // lower chainbar for cone
    chainbarGoto(CHAINBAR_GRAB, true, false);

    // move forwards until holding cone or timeout
    chassis_mode = CHASSIS_MODE_DIRECT;
    chassisSetPower(45);

    // wait for cone intake
    while (!goliath_holding && time < 9250) {
      delay(1);
    }

    if (time < 9250) {

      goliath_timeout = -1;
      goliathIntake(false);

      // stop chassis
      chassisSetPower(0);
      chassisMove(10.f, 10.f, false, false);
      chassis_mode = CHASSIS_MODE_POSITION;

      // stack cone
      chainbarGoto(CHAINBAR_STACK, true, false);
      delay(100);
      goliathDischarge(true);

      if (time < 9500) {

        goliath_timeout = -1;
        goliathIntake(false);

        chainbarGoto(CHAINBAR_GRAB, true, false);

        delay(200);

        chassisMove(-59.7f, -59.7f, false, false);
        chainbarGoto(CHAINBAR_STACK, true, false);
        delay(100);
        goliathDischarge(true);

        while (!chassisAtTarget(false, CHASSIS_MODE_POSITION)) {
          delay(1);
        }
      }
      else {
        // move back to line
        chassisMove(-49.78f, -49.78f, true, true);
      }
    }
    else {
      // move back to line
      chassisMove(-49.78f, -49.78f, true, true);
    }
  }
  else {
    // move back to line
    chassisMove(-chassis_left / CHASSIS_SCALE_DISTANCE + 4.f, -chassis_right / CHASSIS_SCALE_DISTANCE + 4.f, true, true);
  }

  // move chainbar way back
  chainbarGoto(CHAINBAR_RETRACTED, false, false);

  // shut down goliath
  goliathDisable();

  // rotate to 5 zone
  chassisRotate(-200.f, true, true);

  chassisMove(8.f, 8.f, false, false);

  // drop mogo
  mogoGoto(MOGO_ANGLE_GRAB, true, false);

  delay(min(500, 14675 - time));

  mogoGoto(MOGO_ANGLE_RETRACTED, false, false);

  // move out of zones
  chassisMove(-12.f, -12.f, true, false);

  mogoGoto(MOGO_ANGLE_GRAB, false, false);

  pid_chassis_theta.target_buffer = b;

}
