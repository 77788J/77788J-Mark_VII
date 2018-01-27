#include "macros.h"
#include "claw.h"
#include "chainbar.h"
#include "lift.h"
#include "io_control.h"
#include "math.h"
#include "driver_control.h"

unsigned int stack_size = 0;

void autoStackerUpdate() {
  if (joystick.btn8R) {
    current_macro = MACRO_AUTO_STACKER;
    autoStackerRun();
    current_macro = NONE;
  }
}

void autoStackerRun() {
  if (stack_size < MAX_STACK_SIZE - 1) {

    unsigned int timeout = 0;

    float target = 0;

    // disable driver control of affected subsystems
    driver_claw = false;
    driver_chainbar = false;
    driver_lift = false;

    // make sure claw is fully closed
    clawGoto(CLAW_CLOSED, false, false);
    // if (fabs(claw_angle - CLAW_CLOSED) > 20) delay(200); // wait for claw if it starts too far away

    // make sure the chainbar is completely extended
    chainbarGoto(CHAINBAR_GRAB, false, false);

    // raise the lift to stack height
    timeout = 0;
    target = max(LIFT_HEIGHT_MIN, 1.f + (2.8f * stack_size));
    while (lift_height < target && timeout < target * 750) {
      liftSetPower(100);
      delay(20);
      timeout += 20;
    }
    liftSetPower(0);

    // move the chainbar into stack position
    chainbarGoto(CHAINBAR_STACK, true, false);

    // lower lift slightly to make sure cone is fully nested
    timeout = 0;
    target = max(LIFT_HEIGHT_MIN, lift_height - 1.f);
    while (lift_height > target && timeout < 500) {
      liftSetPower(-50);
      delay(20);
      timeout += 20;
    }
    liftSetPower(0);

    // open claw
    clawGoto(CLAW_OPEN, true, false);

    // update stack height
    stack_size++;

    // raise lift to clear top cone
    timeout = 0;
    target = 2.f + (2.8f * stack_size);
    while (lift_height < target && timeout < 1000) {
      liftSetPower(100);
      delay(20);
      timeout += 20;
    }
    liftSetPower(0);

    // extend chainbar back into grab position
    chainbarGoto(CHAINBAR_GRAB, true, false);

    // lower lift back down
    timeout = 0;
    while (lift_height > LIFT_HEIGHT_MIN + 1 && timeout < lift_height * 1000) {
      liftSetPower(-100);
      delay(20);
      timeout += 20;
    }
    liftSetPower(0);

    // re-enable driver control of affected subsystems
    driver_claw = true;
    driver_chainbar = true;
    driver_lift = true;
  }
}
