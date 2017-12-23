#include "pid_control.h"
#include "chassis.h"
#include "pid.h"

// run chasis PID
void pidRunChassis() {
  switch (chassis_mode) {

    // if controlling position
    case (CHASSIS_MODE_POSITION): {

      if (pid_chassis_l.atTarget(false)) pid_chassis_l.resetIntegral();
      if (pid_chassis_r.atTarget(false)) pid_chassis_r.resetIntegral();

      chassisSetPowerExt(
        pid_chassis_l.run(chassis_left, UPDATE_INTERVAL),
        pid_chassis_r.run(chassis_right, UPDATE_INTERVAL));

    } break;

    // if controlling orientation
    case (CHASSIS_MODE_ANGLE): {

      // do stuff

    } break;
  }
}

// run all PIDs
void updateAllPids() {

  // chassis
  pidRunChassis();
}
