#include "macros.h"
#include "goliath.h"
#include "chainbar.h"
#include "lift.h"
#include "io_control.h"
#include "math.h"
#include "driver_control.h"

unsigned int stack_size = 0;

void autoStackerUpdate() {
  if (joystick_secondary.btn7L && (
    joystick_secondary.btn7D_new == 1 ||
    joystick_secondary.btn8D_new == 1 ||
    joystick_secondary.btn8L_new == 1 ||
    joystick_secondary.btn8U_new == 1 ||
    joystick_secondary.btn8R_new == 1 )) {
    current_macro = MACRO_AUTO_STACKER;

    // determine stack size
    if (joystick_secondary.btn7D_new == 1) stack_size = 0;
    if (joystick_secondary.btn8D_new == 1) stack_size = 1;
    if (joystick_secondary.btn8L_new == 1) stack_size = 2;
    if (joystick_secondary.btn8R_new == 1) stack_size = 3;
    if (joystick_secondary.btn8U_new == 1) stack_size = 4;

    while (joystick_secondary.btn7L && stack_size < MAX_STACK_SIZE) {
      autoStackerRun();
    }
    current_macro = NONE;
  }
}

void autoStackerRun() {
  if (stack_size < MAX_STACK_SIZE) {

    // disable driver control of affected subsystems
    driver_goliath = false;
    driver_chainbar = false;
    driver_lift = false;

    // begin to lower ther chainbar
    chainbarGoto(CHAINBAR_GRAB, false, false);

    print("before first lift move");

    // make sure lift is low enough
    if (lift_height > 15.5f) {
      liftGoto(15.5f, false, false);
    }
    else {
      liftGoto(lift_height, false, false);
    }
    pid_lift_enabled = true;

    print("lift has started moving");

    // wait until everything is in position or cone is in goliath
    int timeout = 0;
    while (!(chainbarAtTarget(false) && liftAtTarget(false)) && !goliath_holding && timeout < 1000) {
      delay(1);
      timeout += 1;
      if (!joystick.btn7R) stopMacro();
    }

    print("has cone");

    // begin to raise the lift
    // liftGoto((stack_size * 2.8f) + 2.5f, false, false);
    pid_lift_enabled = false;
    liftSetPower(100);

    // wait until lift is above stack or will be in 500ms
    while (lift_height + (lift_speed * (powerLevelMain() / 7.91f) * .5f) < (stack_size * 2.8f) + 2.5f) {
      delay(1);
      if (!joystick.btn7R) stopMacro();
    }

    // move chainbar in
    chainbarGoto(CHAINBAR_STACK, true, false);

    // move lift down
    liftSetPower(-50);
    delay(200);
    liftSetPower(10);
    delay(50);
    liftSetPower(0);

    // release goliath and move lift up
    timeout = time;
    goliathDischarge(false);
    pid_lift_enabled = true;
    liftGoto((stack_size * 2.8f) + 4.5f, true, false);
    while (time < timeout + 1000) {
      delay(1);
    }

    // increment stack size
    stack_size++;

    // stop goliath
    goliathDisable();

    // move chainbar out
    chainbarGoto(CHAINBAR_GRAB, false, false);

    // wait for chainbar to be out enough for lift to safely descend
    while (chainbar_angle > 35.f) {
      delay(1);
      if (!joystick.btn7R) stopMacro();
    }

    // switch goliath back to intake mode
    goliath_holding = false;
    goliath_spinning = false;
    goliathIntake(false);

    // re-enable driver control of affected subsystems
    driver_goliath = true;
    driver_chainbar = true;

  }
}
