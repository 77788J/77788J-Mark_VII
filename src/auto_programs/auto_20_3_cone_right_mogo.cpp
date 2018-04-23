#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "chainbar.h"
#include "mogo.h"
#include "goliath.h"
#include "math.h"


void autoRunRight203ConeMogo() {

  float b = pid_chassis_theta.target_buffer;
  pid_chassis_theta.target_buffer = 3.f;

  // move to mogo
  chassisMove(55.81f, 55.81f, true, true);

  // intake mogo
  mogoGoto(MOGO_ANGLE_EXTENDED, true, false);
  delay(1000);

  // stack (?) preload
  goliathDischarge(true);

  if (auto_cone) {

    // switch goliath back to intake mode
    goliath_timeout = -1;
    goliathIntake(false);

    // move backwards a bit
    chassisMove(-8.f, -8.f, true, false);

    // lower chainbar for second cone
    chainbarGoto(CHAINBAR_GRAB, true, false);

    // move forwards until holding second cone
    chassis_mode = CHASSIS_MODE_DIRECT;
    chassisSetPower(30);

    // wait for cone intake
    while (!goliath_holding && time < 9000) {
      delay(1);
    }

    // stop chassis
    chassisSetPower(0);
    chassisMove(0, 0, false, false);
    chassis_mode = CHASSIS_MODE_POSITION;

    // stack second cone
    chainbarGoto(CHAINBAR_STACK, true, false);
    goliathDischarge(true);

    // lower chainbar for third cone
    chainbarGoto(CHAINBAR_GRAB, true, false);

    // move forwards until holding third cone
    chassis_mode = CHASSIS_MODE_DIRECT;
    chassisSetPower(55);

    // wait for cone intake
    while (!goliath_holding && time < 8750) {
      delay(1);
    }

    // stop chassis
    chassisSetPower(0);
    chassisMove(0, 0, false, false);
    chassis_mode = CHASSIS_MODE_POSITION;

    // start moving back
    chassisMove(-chassis_left / CHASSIS_SCALE_DISTANCE + 2.f, -chassis_right / CHASSIS_SCALE_DISTANCE + 2.f, false, false);

    // stack cone
    pid_lift_enabled = false;
    liftSetPower(100);
    while (lift_height < 11.f) {
      delay(1);
    }
    liftSetPower(0);

    // stack third cone
    chainbarGoto(CHAINBAR_STACK, true, false);
    liftSetPower(-100);
    delay(400);
    liftSetPower(0);
    goliathDischarge(false);
    liftSetPower(100);
    while (lift_height < 12.f) {
      delay(1);
    }
    liftSetPower(0);
  }

  // make sure mogo is lifted all the way
  pid_mogo_enabled = false;
  mogoSetPower(100);
  delay(250);
  mogoSetPower(0);
  pid_mogo_enabled = true;

  // move chainbar way back
  chainbarGoto(CHAINBAR_RETRACTED, false, false);

  // shut down goliath and lower lift
  goliathDisable();
  liftGoto(LIFT_HEIGHT_MIN, false, false);

  // move back to line
  chassisMove(-chassis_left / CHASSIS_SCALE_DISTANCE + 2.f, -chassis_right / CHASSIS_SCALE_DISTANCE + 2.f, true, true);

  // rotate parallel to 20 zone
  chassisRotate(-136.4f, true, true);

  // move to center of line
  chassisMove(22.9f, 22.9f, true, true);

  // rotate towards 20 zone
  chassisRotate(-90.f, true, true);

  // go forwards to 20
  chassisMove(50.f, 50.f, false, false);

  // go forwards to 20
  delay(1400);

  // drop mogo
  mogoGoto(MOGO_ANGLE_DROP, false, false);

  // move out of zones
  chassisMove(-30.f, -30.f, true, false);

  // get mogo ready for match
  mogoGoto(MOGO_ANGLE_GRAB, false, false);

  pid_chassis_theta.target_buffer = b;
}
