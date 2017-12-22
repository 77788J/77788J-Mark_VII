#include "main.h"
#include "driver_control.h"
#include "motor_control.h"

void operatorControl() {

	// start the timer
	startTimer();

	// start the motor control task
	startMotorTask();

	// start the driver control task
	driverControlStart();

	while (true) {
		delay(20);
	}
}
