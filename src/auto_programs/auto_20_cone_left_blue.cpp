#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "claw.h"
#include "math.h"


void autoRunLeftBlue20Cone() {

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

  // lift mogo lifter
  timeout = 0;
  mogoGoto(MOGO_ANGLE_EXTENDED, false, false);
  while (!mogoAtTarget(false) && timeout < mogoGetTimeout(MOGO_ANGLE_EXTENDED)) {
    timeout++;
    delay(1);
  }

  // go backwards
  chassisMove(-90, -90, true, true);

  // rotate
  chassisRotate(131.6f, true, false);

  // move foreward slightly
  chassisMove(50, 50, true, true);

  // rotate
  chassisRotate(85, true, true);

  // move foreweard
  timeout = 0;
  chassisMove(60, 60, false, false);
  while (!chassisAtTarget(false, CHASSIS_MODE_POSITION) && timeout < 2000) {
    delay(1);
    timeout++;
  }

  // lower mogo slightly and move backwards
  mogoGoto(150, false, false);
  chassisMove(-50, -50, true, false);


  chassisMove(0, 0, false, false);
  pid_chassis_theta.target_buffer = b;

}
