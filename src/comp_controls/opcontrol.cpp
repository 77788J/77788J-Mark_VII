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
		print("MOGO LIFTER\n");
		printf("\tLEFT\t%d\n", analogRead(1));
		printf("\tRIGHT\t%d\n", analogRead(2));
		print("\n\n\n");

		delay(1000);
	}
}
