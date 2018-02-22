#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "goliath.h"
#include "chainbar.h"
#include "mogo.h"
#include "math.h"


void autoRunBullet() {

  // retract/disable everything for safety
  chainbarGoto(CHAINBAR_RETRACTED, false, false);
  goliathDisable();
  mogoGoto(MOGO_ANGLE_RETRACTED, false, false);

  // move
  chassisMove(-BULLET_DISTANCE, -BULLET_DISTANCE, true, true);

  // no more move
  chassisMove(0, 0, false, false);

}
