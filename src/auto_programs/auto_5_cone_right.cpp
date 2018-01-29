#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "claw.h"
#include "math.h"


void autoRunRight5Cone() {

  float b = pid_chassis_theta.target_buffer;
  pid_chassis_theta.target_buffer = 2.f;

  // move to mogo
  chassisMove(58.81f, 58.81f, true, true);

  // intake mogo
  mogoGoto(MOGO_ANGLE_EXTENDED, true, false);
  delay(1000);

  // stack (?) preload
  clawGoto(CLAW_OPEN, true, false);
  delay(100);

  // move back to line
  chassisMove(-49.78f, -49.78f, true, true);

  // rotate to 5 zone
  chassisRotate(-200.f, true, true);

  chassisMove(1.f, 1.f, true, false);

  // drop mogo
  mogoGoto(MOGO_ANGLE_GRAB, true, false);

  // move out of zones
  chassisMove(-30.f, -30.f, true, false);

  // get mogo ready for match
  mogoGoto(MOGO_ANGLE_GRAB, false, false);

  pid_chassis_theta.target_buffer = b;
}
