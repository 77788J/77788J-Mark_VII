#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "claw.h"
#include "math.h"


void autoRunLeft20Cone() {

  float b = pid_chassis_theta.target_buffer;
  pid_chassis_theta.target_buffer = 2.f;

  // move to mogo
  chassisMove(58.81f, 58.81f, true, true);

  // intake mogo
  mogoGoto(MOGO_ANGLE_EXTENDED, true, false);
  delay(100);

  // stack (?) preload
  clawGoto(CLAW_OPEN, true, false);
  delay(100);

  // move back to line
  chassisMove(-49.78f, -49.78f, true, true);

  // rotate parallel to 20 zone
  chassisRotate(-136.4f, true, true);

  // move to center of line
  chassisMove(31.4f, 31.4f, true, true);

  // rotate towards 20 zone
  chassisRotate(-90.f, true, true);

  // go forwards to 20
  chassisMove(45.f, 45.f, true, false);

  // drop mogo
  mogoGoto(MOGO_ANGLE_DROP, false, false);

  // move out of zones
  chassisMove(-30.f, -30.f, true, false);

  // get mogo ready for match
  mogoGoto(MOGO_ANGLE_GRAB, false, false);

  pid_chassis_theta.target_buffer = b;
}
