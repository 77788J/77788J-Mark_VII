#include "main.h"
#include "controller.h"
#include "auto_picker.h"
#include "chassis.h"
#include "autos.h"
#include "chainbar.h"
#include "lift.h"
#include "goliath.h"
#include "mogo.h"

// declare timeout varaibles
unsigned int timeout;
unsigned int max_timeout;

void autonomous() {

  // // reset PIDs
  // chainbarGoto(CHAINBAR_STACK, false, false);
  // goliathIntake(false);
  // mogoGoto(MOGO_ANGLE_GRAB, false, false);
  // chassis_mode = CHASSIS_MODE_DIRECT;

  // start background tasks
  startTimer();
  startController();

  // reset timeout
  timeout = 0;
  max_timeout = 0;
  time = 0;

  // pick the side/color combo to run
  switch (auto_side) {

    case (LEFT): {
      switch (auto_start) {
        case (START_MOGO): runAutoLeftMogo(auto_variation); break;
        case (START_BULLET): runAutoLeftBullet(auto_variation); break;
        case (START_STATIONARY): runAutoLeftStationary(auto_variation); break;
      }
    }; break;

    case (RIGHT): {
      switch (auto_start) {
        case (START_MOGO): runAutoRightMogo(auto_variation); break;
        case (START_BULLET): runAutoRightBullet(auto_variation); break;
        case (START_STATIONARY): runAutoRightStationary(auto_variation); break;
      }
    }; break;
  }
}
