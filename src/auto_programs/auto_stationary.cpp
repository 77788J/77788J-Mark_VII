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


void autoRunStationary() {

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

}
