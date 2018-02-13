#include "macros.h"
#include "goliath.h"
#include "chainbar.h"
#include "lift.h"
#include "io_control.h"
#include "math.h"
#include "driver_control.h"

void stationaryLoaderUpdate() {
  if (joystick.btn8R || joystick_secondary.btn8R) {
    current_macro = MACRO_STATIONARY_LOADER;
    assistedStackerRun();
    current_macro = NONE;
  }
}

void stationaryLoaderRun() {

  float target = 0;

  // disable driver control of affected subsystems
  driver_goliath = false;
  driver_chainbar = false;

  // wait for user to raise lift above stack or stationary
  target = lift_height + 4.f;
  while (lift_height < STATIONARY_HEIGHT + 3 || lift_height < target) {
    delay(1);
  }
  
  // lower 4-bar
  chainbarGoto(CHAINBAR_GRAB, true, false);

  // spit out cone
  goliathDischarge(false);

  // store target height of lift
  target = lift_height + 4.f;

  // wait for lift to raise above target
  while (lift_height < target) {
    delay(1);
  }

  // retract 4-bar
  chainbarGoto(CHAINBAR_STACK, false, false);

  // switch goliath back to intake mode
  goliathIntake(false);

  // re-enable driver control of affected subsystems
  driver_goliath = true;
  driver_chainbar = true;
}
