#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "claw.h"
#include "math.h"


void autoRunSkills() {

  // raise lift out of the way
  liftGoto(12.f, false, false);

  // move up to mogo
  chassisMove(30.794f, 30.794f, true, true);

  // lower lift slightly
  liftGoto(9.f, true, true);

  // open claw
  clawGoto(CLAW_OPEN, false, false);
  delay(500);

  // raise lift back out of way
  liftGoto(12.f, true, false);

  // raise mogo lifter
  mogoGoto(MOGO_ANGLE_EXTENDED, true, true);

  // turn around
  chassisRotate(-180.f, true, true);

  // move to line
  chassisMove(30.794f, 30.794f, true, true);

  // rotate parallel to line
  chassisRotate(-90.f, true, true);

  // move to center of line
  chassisMove(17.208f, 17.208f, true, true);

  // point towards 20 zone
  chassisRotate(90.f, true, true);

  // move into 20 zone
  chassisMove(27.631f, 27.631f, true, true);

  // drop mogo into 20 (or 10 if it misses) and move out
  mogoGoto(MOGO_ANGLE_DROP, false, false);
  chassisMove(-27.631f, -27.631f, true, true);

  // retract mogo lifter and move forward slowly to align with starting bar
  mogoGoto(MOGO_ANGLE_RETRACTED, false, false);
  chassis_mode = CHASSIS_MODE_DIRECT;
  chassisSetPower(25);
  delay(2500);

  // back up a bit to turn
  chassisMove(-8.452, -8.452, true, true);

  // rotate parallel to line
  chassisRotate(-90.f, true, true);

  // move forward a bit
  chassisMove(17.096f, 17.096f, true, true);

  // rotate to face mogo
  chassisRotate(-90.f, true, true);

  // lower mogo lifter
  mogoGoto(MOGO_ANGLE_GRAB, true, false);

  // move to mogo
  chassisMove(33.263f, 33.263f, true, true);

  // raise mogo lifter
  mogoGoto(MOGO_ANGLE_EXTENDED, true, false);

  // rotate to face 10 zone
  chassisRotate(180.f, true, true);

  // move to 10 zone
  chassisMove(41.532f, 41.532f, true, true);

  // lower mogo lifter
  mogoGoto(MOGO_ANGLE_GRAB, true, false);

  // move back a bit to rotate
  chassisMove(-10.481f, -10.381f, true, true);

  // rotate to face mogo
  chassisRotate(-180.f, true, true);

  // move to mogo
  chassisMove(64.950f, 64.950f, true, true);

  // lift mogo
  mogoGoto(MOGO_ANGLE_EXTENDED, true, false);

  // move to line
  chassisMove(37.783f, 37.783f, true, true);

  // align with starting bar
  chassis_mode = CHASSIS_MODE_DIRECT;
  chassisSetPower(25);
  delay(5000);

  // move back to line
  chassisMove(-9.833f, -9.833f, true, true);

  // rotate parallel to line
  chassisRotate(-90.f, true, true);

  // move to center of line
  chassisMove(16.043f, 16.043f, true, true);

  // rotate to face 20 zone
  chassisRotate(90.f, true, true);

  // move into 20 zone
  chassisMove(29.631f, 29.631f, true, true);

  // drop mogo into 20 (or 10 if it misses) and move out
  mogoGoto(MOGO_ANGLE_DROP, false, false);
  chassisMove(-29.631f, -29.631f, true, true);

  // retract mogo lifter and move forward slowly to align with starting bar
  mogoGoto(MOGO_ANGLE_RETRACTED, false, false);
  chassis_mode = CHASSIS_MODE_DIRECT;
  chassisSetPower(25);
  delay(2500);

  // move back to line
  chassisMove(-9.574f, -9.574f, true, true);

  // rotate parallel to line
  chassisRotate(-90.f, true, true);

  // move forward a bit
  chassisMove(17.471f, 17.471f, true, true);

  // rotate to face mogo
  chassisRotate(-90.f, true, true);

  // lower mogo lifter
  mogoGoto(MOGO_ANGLE_GRAB, true, false);

  // move to mogo
  chassisMove(29.759f, 29.759f, true, true);

  // rotate to face 10 zone
  chassisRotate(180.f, true, true);

  // move to 10 zone
  chassisMove(39.332f, 39.332f, true, true);

  // lower mogo lifter
  mogoGoto(MOGO_ANGLE_GRAB, true, false);

  // move backwards to line
  chassisMove(-9.187f, -9.187f, true, true);

  // retract mogo lifter
  mogoGoto(MOGO_ANGLE_RETRACTED, false, false);

  // rotate parallel to line
  chassisRotate(90.f, true, true);

  // move to end of line
  chassisMove(48.513f, 48.513f, true, true);

  // point towards parking spot
  chassisRotate(45.f, true, true);

  // park
  chassisMove(49.953f, 49.953f, true, true);

}
