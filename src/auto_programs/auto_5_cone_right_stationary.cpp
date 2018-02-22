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


void autoRunRight5ConeStationary() {

  float b = pid_chassis_theta.target_buffer;
  pid_chassis_theta.target_buffer = 2.f;

  // rotate to face mogo
  chassisRotate(90.f, true, true);

  // move to mogo
  chassisMove(58.81f, 58.81f, true, true);

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
    chassisMove(-6.f, -6.f, true, false);

    // lower chainbar for second cone
    chainbarGoto(CHAINBAR_GRAB, true, false);

    // move forwards until holding second cone
    chassis_mode = CHASSIS_MODE_DIRECT;
    chassisSetPower(45);

    // wait for cone intake
    while (!goliath_holding && time < 15000) {
      delay(1);
    }

    // stop chassis
    chassisSetPower(0);
    chassisMove(0, 0, false, false);
    chassis_mode = CHASSIS_MODE_POSITION;

    // stack second cone
    chainbarGoto(CHAINBAR_STACK, true, false);
    goliathDischarge(true);
  }

  // // make sure there's enough time for a third cone
  // if (time < 25000) {
  //
  //   // switch goliath back to intake mode
  //   goliath_timeout = -1;
  //   goliathIntake(false);
  //
  //   // lower chainbar for second cone
  //   chainbarGoto(CHAINBAR_GRAB, true, false);
  //
  //   // move forwards until holding second cone
  //   chassis_mode = CHASSIS_MODE_DIRECT;
  //   chassisSetPower(45);
  //
  //   // wait for cone intake
  //   while (!goliath_holding && time < 25000) {
  //     delay(1);
  //   }
  //
  //   // stop chassis
  //   chassisSetPower(0);
  //   chassisMove(0, 0, false, false);
  //   chassis_mode = CHASSIS_MODE_POSITION;
  //
  //   // raise lift a bit
  //   liftGoto(9.f, true, true);
  //
  //   // stack third cone
  //   chainbarGoto(CHAINBAR_STACK, true, false);
  //   goliathDischarge(true);
  // }

  // move chainbar way back
  chainbarGoto(CHAINBAR_RETRACTED, true, false);

  // shut down goliath and lower lift
  goliathDisable();
  liftGoto(LIFT_HEIGHT_MIN, false, false);

  // move back to line
  chassisMove(-49.78f, -49.78f, true, true);

  // rotate to 5 zone
  chassisRotate(-200.f, true, true);

  chassisMove(8.f, 8.f, true, false);

  // drop mogo
  mogoGoto(MOGO_ANGLE_GRAB, true, false);

  delay(500);

  // move out of zones
  chassisMove(-30.f, -30.f, true, false);

  // get mogo ready for match
  mogoGoto(MOGO_ANGLE_GRAB, false, false);

  pid_chassis_theta.target_buffer = b;
}
