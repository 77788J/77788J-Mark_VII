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

  // move 18 inches
  chassisMove(18, 18, true, true);

  print("done");
}
