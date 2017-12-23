#include "main.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "math.h"

void operatorControl() {

	// start the central controller
	startController();

	// start the timer
	startTimer();

	while (true) {
		printf("%f, %d\n", motor_chassis_fl.getVelocity(), round(motor_chassis_fl.getVelocity()) == 0);

		delay(1900);
	}
}
