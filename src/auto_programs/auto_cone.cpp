#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "claw.h"
#include "math.h"


void autoRunCone() {

  unsigned int timeout = 0;
  unsigned int max_timeout = 0;
  float b = pid_chassis_theta.target_buffer;
  pid_chassis_theta.target_buffer = 2.f;

  // move to mogo while raising lift
  liftGoto(15.f, false, false);
  chassisMove(105.f, 105.f, true, true);

  // lower lift
  liftGoto(9.f, false, false);
  delay(500);

  // open claw
  clawGoto(CLAW_OPEN, false, false);
  delay(500);

  // go backwards
  chassisMove(-40, -40, true, true);
  chassisMove(0, 0, false, false);
  pid_chassis_theta.target_buffer = b;

}
