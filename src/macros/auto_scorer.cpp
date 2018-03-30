#include "macros.h"
#include "goliath.h"
#include "chainbar.h"
#include "lift.h"
#include "mogo.h"
#include "chassis.h"
#include "io_control.h"
#include "math.h"
#include "driver_control.h"

void autoScorerUpdate() {
  if (joystick.btn7L) {
    current_macro = MACRO_AUTO_SCORER;
    autoScorerRun();
    current_macro = NONE;
  }
}

void autoScorerRun() {

  // disable driver control of affected subsystems
  driver_goliath = false;
  driver_chainbar = false;
  driver_chassis = false;
  driver_lift = false;
  driver_mogo = false;

  // lower mogo
  mogoGoto(MOGO_ANGLE_GRAB, false, false);
  delay(345);

  // raise lift while expelling goliath
  liftGoto(min(lift_height + 16.f, LIFT_HEIGHT_MAX), false, false);
  pid_lift_enabled = true;
  goliathDischarge(false);

  // wait a small bit
  delay(275);

  // move chassis backwards
  chassisMove(-18.f, -18.f, true, false);

  // switch goliath back to intake mode
  goliath_holding = false;
  goliath_spinning = false;
  goliathIntake(false);

  // re-enable driver control of affected subsystems
  driver_goliath = true;
  driver_chainbar = true;
  driver_chassis = true;
  driver_lift = true;
  driver_mogo = true;
}
