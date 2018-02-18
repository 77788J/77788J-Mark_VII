#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "goliath.h"
#include "chainbar.h"
#include "mogo.h"
#include "math.h"


void autoRunLeftLandslideStationary() {

  // rotate to face mogo
  chassisRotate(-90.f, true, true);

  // move to mogo
  chassisMove(58.81f, 58.81f, true, true);

  // intake mogo
  mogoGoto(MOGO_ANGLE_EXTENDED, true, false);
  delay(1000);

  // stack (?) preload
  goliathDischarge(true);

  // shutdown goliath, retract chainbar, and rotate
  goliathDisable();
  chainbarGoto(CHAINBAR_RETRACTED, false, false);
  chassisRotate(135.f, true, true);

  // move forward a bit
  chassisMove(26.6f, 26.6f, true, true);

  // rotate 180
  chassisRotate(180.f, true, true);

  // push mogos into corner
  chassisMove(93.f, 93.f, true, false);

  // stop chassis (in case of timeout)
  chassisMove(0, 0, false, false);

}
