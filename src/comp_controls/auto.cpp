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

  chassisMove(18, 18, true, true);

  while (true) {
    print("done\n");
    delay(1000);
  }

}
