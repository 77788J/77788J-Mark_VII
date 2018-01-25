#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "claw.h"
#include "chainbar.h"
#include "math.h"


void autoRunLeftStationaryFlip() {

  int max_timeout;
  int timeout = 0;

  // raise lift and extend 4-bar
  liftGoto(LIFT_HEIGHT_STATIONARY, false, false);
  chainbarGoto(CHAINBAR_GRAB, false, false);
  max_timeout = max(liftGetTimeout(LIFT_HEIGHT_STATIONARY), chainbarGetTimeout(CHAINBAR_GRAB));
  while (!(liftAtTarget(false) && chainbarAtTarget(false)) && timeout < max_timeout) {
    delay(1);
    timeout++;
  }

  // move to stationary goal
  chassisMove(29.28f, 29.28f, true, true);

  // lower lift slightly and open claw
  liftGoto(LIFT_HEIGHT_STATIONARY - 2.f, false, false);
  delay(200);
  clawGoto(CLAW_OPEN, true, false);

  // back up to line
  chassisMove(-20.98f, -20.98f, true, false);

  // turn
  chassisRotate(-135.f, true, true);

  // move along line
  chassisMove(9.49f, 9.49f, true, false);

  // turn
  chassisRotate(107.8f, true, true);

  // move forward (and make sure mogo lifter is retracted)
  mogoGoto(MOGO_ANGLE_RETRACTED, false, false);
  chassisMove(36.57f, 36.57f, true, false);

  // lower lift around mogo
  liftGoto(LIFT_HEIGHT_MIN, true, true);

  // back away and tip mogo
  chassisMove(-21.61f, -21.61f, true, false);

  // lower mogo lift again for driver
  mogoGoto(MOGO_ANGLE_GRAB, true, false);

}
