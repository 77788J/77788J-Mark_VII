#include "main.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "mogo.h"
#include "math.h"

void autonomous() {

  // start background tasks
  startTimer();
  startController();

  // stop all subsystems (they do random stuff at the beginnig for some reason)
  chassisSetPower(0);
  mogoSetPower(0);

  chassisMove(8, 8, true, true);

  print("done");
}
