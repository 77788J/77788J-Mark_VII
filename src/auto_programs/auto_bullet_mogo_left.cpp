#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "goliath.h"
#include "chainbar.h"
#include "mogo.h"
#include "math.h"


void autoRunLeftBulletMogo() {

  // retract/disable everything for safety
  chainbarGoto(CHAINBAR_RETRACTED, false, false);
  goliathDisable();
  mogoGoto(MOGO_ANGLE_RETRACTED, false, false);

  // rotate
  chassisRotate(-150.f, true, false);

  // move
  chassisMove(95.f, 95.f, true, false);

  // no more move
  chassisMove(0, 0, false, false);

}
