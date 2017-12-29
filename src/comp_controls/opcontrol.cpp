#include "main.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "mogo.h"
#include "math.h"

void operatorControl() {

	// start the central controller
	startController();

	// start the timer
	startTimer();

	while (true) {
		print("CHASSIS\n");
		printf("\tLEFT\t%f\n", chassis_left);
		printf("\tRIGHT\t%f\n", chassis_right);
		printf("\tORIENTATION\t%f\n", chassis_angle);
		print("\n");
		print("MOGO LIFTER\n");
		printf("\tLEFT\t%f\n", mogo_angle_l);
		printf("\tRIGHT\t%f\n", mogo_angle_r);
		printf("\tAVERAGE\t%f\n", mogo_angle);
		printf("\tTARGET\t%f\n", pid_mogo.getTarget());
		printf("\tPOWER\t%d\n", motor_mogo.getPower());
		print("\n\n\n");

		if (joystick.btn7U) {
			chassisRotate(90, true, true);
			printf("\n\n\n%f\n\n\n", motor_chassis_fl.getVelocity());
		}

		delay(1000);
	}
}
