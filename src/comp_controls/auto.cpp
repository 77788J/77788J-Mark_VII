#include "main.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "math.h"

// timeout varaibles
unsigned int timeout;
unsigned int max_timeout;

// start tasks and stuff
void autoSetup() {

    // start background tasks
    startTimer();
    startController();
}

void autonomous() {
  autoSetup();

  chassisMove(95.900620, 93.975151, false, false);
	liftGoto(4.500000, false, false);
	mogoGoto(100.000000, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutPosition(95.900620, 93.975151));
	max_timeout = max(max_timeout, liftGetTimeout(4.500000));
	max_timeout = max(max_timeout, mogoGetTimeout(100.000000));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION) || !liftAtTarget(true) || !mogoAtTarget(true))) {
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


	chassisMove(-74.409935, -75.093163, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutPosition(-74.409935, -75.093163));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
		timeout += 1;
		delay(1);
	}


	chassisRotate(-46.500000, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutAngle(-46.500000));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
		timeout += 1;
		delay(1);
	}


	chassisMove(-40.745342, -38.012421, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutPosition(-40.745342, -38.012421));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
		timeout += 1;
		delay(1);
	}


	chassisRotate(-90.600006, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutAngle(-90.600006));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_ANGLE))) {
		timeout += 1;
		delay(1);
	}


	chassisMove(61.242233, 55.962730, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutPosition(61.242233, 55.962730));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
		timeout += 1;
		delay(1);
	}


	chassisMove(-56.521736, -58.571426, false, false);
	timeout = 0;
	max_timeout = 0;
	max_timeout = max(max_timeout, chassisGetTimeoutPosition(-56.521736, -58.571426));
	while (timeout < max_timeout && (!chassisAtTarget(true, CHASSIS_MODE_POSITION))) {
		timeout += 1;
		delay(1);
	}

}
