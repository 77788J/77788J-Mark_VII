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


void autoRunLeftStationary2() {

  // raise lift and extend mogo lifter
  mogoGoto(MOGO_ANGLE_EXTENDED, false, false);
  liftGoto(LIFT_HEIGHT_STATIONARY + 2.f, true, true);

  // move to stationary goal
  chassisMove(22.5f, 22.5f, true, true);
  delay(200);

  // lower lift slightly
  liftGoto(LIFT_HEIGHT_STATIONARY - 4.f, true, true);
  delay(300);

  // discharge and raise lift
  goliathDischarge(false);
  liftGoto(LIFT_HEIGHT_STATIONARY + 2.f, true, false);
  delay(100);

  // back up and retract chainbar
  chainbarGoto(CHAINBAR_RETRACTED, false, false);
  chassisMove(-12.5f, -12.5f, true, true);

  // lower lift and mogo lifter
  liftGoto(LIFT_HEIGHT_MIN, false, false);
  mogoGoto(MOGO_ANGLE_RETRACTED, false, false);

  // intake goliath
  goliathIntake(false);

  // rotate to face cone and lower chainbar
  chainbarGoto(CHAINBAR_GRAB, false, false);
  chassisRotate(-101.9f, true, true);

  // reset encoders
  chassisResetSensors();

  // intake goliath
  goliathIntake(false);

  // move chassis to cone
  chassisMove(20.f, 20.f, true, true);
  delay(200);
  chassis_mode = CHASSIS_MODE_DIRECT;
  chassisSetPower(30);

  // grab cone
  while (!goliath_holding) {
    delay(1);
  }

  // raise 4 bar and move back to loader
  chainbarGoto(CHAINBAR_STACK, false, false);
  delay(200);
  liftGoto(LIFT_HEIGHT_STATIONARY + 4.f, false, false);
  chassisMove(-chassis_left / CHASSIS_SCALE_DISTANCE - 1.3f, -chassis_right / CHASSIS_SCALE_DISTANCE - 1.3f, true, true);

  // raise lift and extend mogo lifter
  mogoGoto(MOGO_ANGLE_EXTENDED, false, false);

  // rotate towards loader
  chassisRotate(105.f, true, true);

  // move to stationary goal
  chassisMove(15.5f, 15.5f, true, true);
  delay(200);

  // lower lift slightly
  liftGoto(LIFT_HEIGHT_STATIONARY + 1.f, true, true);
  delay(300);

  // discharge and raise lift
  goliathDischarge(false);
  delay(100);
  liftGoto(LIFT_HEIGHT_STATIONARY + 8.f, true, false);

  // back up and retract chainbar
  chainbarGoto(CHAINBAR_RETRACTED, false, false);
  chassisMove(-20.5f, -20.5f, true, true);

  // lower lift and mogo lifter
  liftGoto(LIFT_HEIGHT_MIN, false, false);
  mogoGoto(MOGO_ANGLE_GRAB, false, false);

}
