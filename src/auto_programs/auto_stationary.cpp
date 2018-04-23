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

  // raise lift and extend chainbar
  mogoGoto(MOGO_ANGLE_EXTENDED, false, false);
  liftGoto(LIFT_HEIGHT_STATIONARY + 2.f, true, true);

  // move to stationary goal
  chassisMove(22.5f, 22.5f, true, true);

  // lower lift slightly and open claw
  liftGoto(LIFT_HEIGHT_STATIONARY - 4.f, true, true);

  // discharge and raise lift
  goliathDischarge(false);
  liftGoto(LIFT_HEIGHT_STATIONARY + 2.f, true, false);

  // back up a bit and retract chainbar
  chainbarGoto(CHAINBAR_RETRACTED, false, false);
  chassisMove(-8.391f, -8.391f, true, true);

  // lower lift
  liftGoto(LIFT_HEIGHT_MIN, false, false);

}
