#include "main.h"
#include "controller.h"
#include "driver_control.h"
#include "io_control.h"
#include "recorder.h"
#include "macros.h"
#include "chassis.h"
#include "lift.h"
#include "chainbar.h"
#include "claw.h"
#include "goliath.h"
#include "mogo.h"
#include "math.h"

void operatorControl() {

	// start the central controller
	startController();

	// start the timer
	startTimer();

	// start the macros listener
	macrosStartListener();

	while (true) {

		// only debug if not recording so console isn't cluttered
		if (!RECORDING_ENABLED) {
			print("CHASSIS\n");
			printf("\tLEFT\t%f\n", chassis_left);
			printf("\tRIGHT\t%f\n", chassis_right);
			printf("\tVELOCITY LEFT\t%f\n", motor_chassis_fl.getVelocity());
			printf("\tVELOCITY RIGHT\t%f\n", motor_chassis_fr.getVelocity());
			printf("\tORIENTATION\t%f\n", chassis_angle);
			printf("\tAP FILTER ANGLE\t%f\n", orientation_ap);
			print("\n");
			print("MOGO LIFTER\n");
			printf("\tLEFT\t%f\n", mogo_angle_l);
			printf("\tRIGHT\t%f\n", mogo_angle_r);
			printf("\tAVERAGE\t%f\n", mogo_angle);
			printf("\tTARGET\t%f\n", pid_mogo.getTarget());
			printf("\tPOWER\t%d\n", motor_mogo.getPower());
			print("LIFT\n");
			printf("\tANGLE\t%f\n", lift_angle);
			printf("\tHEIGHT\t%f\n", lift_height);
			printf("\tTARGET\t%f\n", pid_lift.getTarget());
			print("GOLIATH\n");
			printf("\tANGLE\t%f\n", goliath_angle);
			printf("\tVELOCITY\t%f\n", motor_goliath.getVelocity());
			print("4 BAR\n");
			printf("\tANGLE\t%f\n", chainbar_angle);
			print("\n\n\n");
		}

		if (joystick.btn7L && joystick.btn7R) {
			driver_chassis = false;
			driver_mogo = false;
			driver_lift = false;
			driver_chainbar = false;
			driver_claw = false;

			autonomous();

			driver_chassis = true;
			driver_mogo = true;
			driver_lift = true;
			driver_chainbar = true;
		}

		delay(1000);
	}
}
