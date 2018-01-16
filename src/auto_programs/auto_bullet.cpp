#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "math.h"


void autoRunBullet() {

  chassisMove(BULLET_DISTANCE, BULLET_DISTANCE, true, true);

  chassisMove(0, 0, false, false);

}
