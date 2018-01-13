#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "claw.h"
#include "math.h"


void autoRunLeftBlue20Cone() {

  unsigned int timeout = 0;
  unsigned int max_timeout = 0;

  chassisMove(66.832298, 66.149063, false, false);
	liftGoto(4.500000, false, false);
	mogoGoto(100.000000, false, false);
	clawGoto(145.000000, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutPosition(66.832298, 66.149063));
	max_timeout = max(max_timeout, liftGetTimeout(4.500000));
	max_timeout = max(max_timeout, mogoGetTimeout(100.000000));
	max_timeout = max(max_timeout, clawGetTimeout(145.000000));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION) || !liftAtTarget(true) || !mogoAtTarget(true) || !clawAtTarget(false))) {
		timeout += 1;
		delay(1);
	}


	chassisMove(0.000000, 0.062112, false, false);
	mogoGoto(200.000000, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutPosition(0.000000, 0.062112));
	max_timeout = max(max_timeout, mogoGetTimeout(200.000000));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION) || !mogoAtTarget(true))) {
		timeout += 1;
		delay(1);
	}


	chassisMove(-56.894409, -57.950310, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutPosition(-56.894409, -57.950310));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
		timeout += 1;
		delay(1);
	}


	chassisRotate(87.100006, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutAngle(87.100006));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
		timeout += 1;
		delay(1);
	}


	chassisMove(34.447205, 34.372669, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutPosition(38.447205, 40.372669));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
		timeout += 1;
		delay(1);
	}


	chassisRotate(83.799988, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutAngle(83.799988));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
		timeout += 1;
		delay(1);
	}


	chassisMove(65.024845, 65.701862, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutPosition(56.024845, 47.701862));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
		timeout += 1;
		delay(1);
	}


	chassisMove(-52.360249, -52.223602, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutPosition(-52.360249, -54.223602));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
		timeout += 1;
		delay(1);
	}

  chassisMove(0.000000, 0.000000, false, false);
liftGoto(4.500000, false, false);
mogoGoto(200.000000, false, false);
clawGoto(145.000000, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(0.000000, 0.000000));
max_timeout = max(max_timeout, liftGetTimeout(4.500000));
max_timeout = max(max_timeout, mogoGetTimeout(200.000000));
max_timeout = max(max_timeout, clawGetTimeout(145.000000));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION) || !liftAtTarget(true) || !mogoAtTarget(true) || !clawAtTarget(false))) {
  timeout += 1;
  delay(1);
}


chassisMove(8.633540, 9.751553, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(8.633540, 9.751553));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


chassisRotate(-104.300003, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutAngle(-109.300003));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
  timeout += 1;
  delay(1);
}


chassisMove(24.596273, 25.776398, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(24.596273, 25.776398));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


chassisRotate(-78.399994, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutAngle(-78.399994));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
  timeout += 1;
  delay(1);
}


mogoGoto(100.000000, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, mogoGetTimeout(100.000000));
while (timeout < max_timeout && (!mogoAtTarget(true))) {
  timeout += 1;
  delay(1);
}


chassisMove(36.024845, 38.385094, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(36.024845, 38.385094));
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

chassisMove(-53.354034, -53.478260, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(-53.354034, -53.478260));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


chassisRotate(-94.000000, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutAngle(-94.000000));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
  timeout += 1;
  delay(1);
}


chassisMove(36.149067, 35.031055, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(36.149067, 35.031055));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


chassisRotate(-76.700012, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutAngle(-76.700012));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
  timeout += 1;
  delay(1);
}


chassisMove(19.378881, 17.639751, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(19.378881, 17.639751));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


chassisMove(-0.062112, 0.000000, false, false);
mogoGoto(100.000000, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(-0.062112, 0.000000));
max_timeout = max(max_timeout, mogoGetTimeout(100.000000));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION) || !mogoAtTarget(true))) {
  timeout += 1;
  delay(1);
}


chassisMove(-28.509315, -25.590061, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(-28.509315, -25.590061));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}

// ANOTHER 20!?!?!?
chassisMove(0.000000, 0.000000, false, false);
liftGoto(4.500000, false, false);
mogoGoto(100.000000, false, false);
clawGoto(145.000000, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(0.000000, 0.000000));
max_timeout = max(max_timeout, liftGetTimeout(4.500000));
max_timeout = max(max_timeout, mogoGetTimeout(100.000000));
max_timeout = max(max_timeout, clawGetTimeout(145.000000));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION) || !liftAtTarget(true) || !mogoAtTarget(true) || !clawAtTarget(false))) {
  timeout += 1;
  delay(1);
}


chassisRotate(-87.599998, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutAngle(-87.599998));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
  timeout += 1;
  delay(1);
}


chassisMove(27.080744, 28.944099, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(27.080744, 28.944099));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


chassisRotate(-86.800011f, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutAngle(-92.300011));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
  timeout += 1;
  delay(1);
}


chassisMove(106.024841, 105.838509, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(106.024841, 105.838509));
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


chassisRotate(51.899994, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutAngle(51.899994));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
  timeout += 1;
  delay(1);
}


chassisMove(31.428570, 30.621117, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(31.428570, 30.621117));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


chassisRotate(-85.800011, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutAngle(-93.300011));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
  timeout += 1;
  delay(1);
}


chassisMove(57.515526, 54.844719, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(57.515526, 54.844719));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


chassisRotate(27.600006, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutAngle(27.600006));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
  timeout += 1;
  delay(1);
}


chassisMove(60.242233, 60.260868, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(41.242233, 38.260868));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}


chassisMove(-55.093166, -54.409935, false, false);
mogoGoto(150, false, false);
timeout = 0;
max_timeout = 0;
max_timeout = max(max_timeout, chassisGetTimeoutPosition(-55.093166, -54.409935));
while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
  timeout += 1;
  delay(1);
}

chassisMove(0, 0, false, false);

}
