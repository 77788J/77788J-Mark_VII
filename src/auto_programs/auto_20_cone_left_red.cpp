#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "claw.h"
#include "math.h"


void autoRunLeftRed20Cone() {

  unsigned int timeout = 0;
  unsigned int max_timeout = 0;

  liftGoto(4.500000, false, false);
mogoGoto(100.000000, false, false);
clawGoto(145.000000, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, liftGetTimeout(4.500000));
max_timeout = max(max_timeout, mogoGetTimeout(100.000000));
max_timeout = max(max_timeout, clawGetTimeout(145.000000));
while (timeout < max_timeout && (!liftAtTarget(true) || !mogoAtTarget(true) || !clawAtTarget(false))) {
  timeout += 1;
  delay(1);
}


chassisMove(16.086956, 15.527950, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(16.086956, 15.527950));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


chassisRotate(-53.799999, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutAngle(-53.799999));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
  timeout += 1;
  delay(1);
}


chassisMove(66.086952, 69.378883, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(66.086952, 69.378883));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


chassisRotate(4.700001, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutAngle(4.700001));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
  timeout += 1;
  delay(1);
}


chassisMove(19.751553, 22.111801, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(19.751553, 22.111801));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


mogoGoto(200.000000, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, mogoGetTimeout(200.000000));
while (timeout < max_timeout && (!mogoAtTarget(true))) {
  timeout += 1;
  delay(1);
}


chassisRotate(178.900009, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutAngle(178.900009));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
  timeout += 1;
  delay(1);
}


chassisMove(88.944099, 91.925461, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(88.944099, 91.925461));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


chassisRotate(-42.500000, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutAngle(-42.500000));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
  timeout += 1;
  delay(1);
}


chassisMove(38.633541, 39.006210, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(38.633541, 39.006210));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


chassisRotate(85.099991, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutAngle(85.099991));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
  timeout += 1;
  delay(1);
}


chassisMove(50.931675, 64.720497, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(50.931675, 64.720497));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


chassisMove(-41.242233, -50.993786, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(-41.242233, -50.993786));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}

}
