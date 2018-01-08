#include "main.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "math.h"

void autonomous() {

  // start background tasks
  startTimer();
  startController();


  chassisMove(79.316765, 76.583847, false, false);
  liftGoto(10.000000, false, false);
  mogoGoto(100.000000, false, false);
  while (!chassisAtTarget(true, CHASSIS_MODE_POSITION) || !mogoAtTarget(true)) {
  	delay(1);
  }


  mogoGoto(200.000000, false, false);
  while (!chassisAtTarget(true, CHASSIS_MODE_POSITION) || !mogoAtTarget(true)) {
  	delay(1);
  }

  print("done");

  chassisRotate(-185.299988, false, false);
  while (!chassisAtTarget(true, CHASSIS_MODE_ANGLE)) {
  	delay(1);
  }


  chassisMove(95.527946, 95.590057, false, false);
  while (!chassisAtTarget(true, CHASSIS_MODE_POSITION)) {
  	delay(1);
  }


  mogoGoto(100.000000, false, false);
  while (!mogoAtTarget(true)) {
  	delay(1);
  }


  chassisMove(-73.291924, -75.279503, false, false);
  while (!chassisAtTarget(true, CHASSIS_MODE_POSITION)) {
  	delay(1);
  }

  print("done");
}
