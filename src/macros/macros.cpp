#include "macros.h"
#include "io_control.h"
#include "driver_control.h"
#include "lift.h"

TaskHandle task_macros;
unsigned char current_macro = NONE;

// kills the macro task and starts a blank one
void stopMacro() {

  // kill the task
  taskDelete(task_macros);

  // reset varaibles for raw driver control
  current_macro = NONE;
  pid_lift_enabled = false;
  driver_chassis = true;
  driver_lift = true;
  driver_claw = true;
  driver_goliath = true;
  driver_mogo = true;
  driver_chainbar = true;

  // restart the task
  macrosStartListener();
}

// start background task with macro listener
void macrosStartListener() {
  task_macros = taskRunLoop(macrosUpdate, UPDATE_INTERVAL);
}

// listen for macros and run them
void macrosUpdate() {
  // autoStackerUpdate();
  assistedStackerUpdate();
  stationaryLoaderUpdate();
  autoScorerUpdate();
  if ((joystick.btn7L && joystick.btn7R) || (joystick_secondary.btn7L && joystick_secondary.btn7R)) stopMacro();
}
