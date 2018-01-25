#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "claw.h"
#include "math.h"


void autoRunRightStationary() {

  // move parallel to stationry goal
  chassisMove(9.333f, 9.333f, true, true);

  // rotate towards stationary goal
  chassisRotate(-90.f, true, true);

  // raise lift
  liftGoto(LIFT_HEIGHT_STATIONARY, true, true);

  // move to stationary goal
  chassisMove(14.455f, 14.455f, true, true);

  // lower lift slightly and open claw
  liftGoto(LIFT_HEIGHT_STATIONARY - 2.f, false, false);
  delay(200);
  clawGoto(CLAW_OPEN, true, false);

  // back up a bit
  chassisMove(-4.391f, -4.391f, true, true);

  // lower lift
  liftGoto(LIFT_HEIGHT_MIN, false, false);

}
