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

    float target = 0;

    // disable driver control of affected subsystems
    driver_claw = false;
    driver_chainbar = false;
    driver_lift = false;

    // make sure claw is fully closed
    clawGoto(CLAW_CLOSED, false, false);
    if (fabs(claw_angle - CLAW_CLOSED) > 20) delay(200); // wait for claw if it starts too far away

    // make sure the chainbar is completely extended
    chainbarGoto(CHAINBAR_GRAB, true, false);

    // raise the lift to stack height
    target = 10.f + (2.8f * stack_size);
    liftGoto(target, false, false);
    while (lift_height < target) {
      delay(1);
    }

    // move the chainbar into stack position
    chainbarGoto(CHAINBAR_STACK, true, false);

    // lower lift slightly to make sure cone is fully nested
    target = lift_height - 1.f;
    liftGoto(target, false, false);
    while (lift_height > target) {
      delay(1);
    }

    // open claw
    clawGoto(CLAW_OPEN, true, false);

    // raise lift to clear top cone
    target = 13.5f + (2.8f * stack_size);
    liftGoto(target, false, false);
    while (lift_height < target) {
      delay(1);
    }

    // extend chainbar back into grab position
    chainbarGoto(CHAINBAR_GRAB, true, false);

    // lower lift back down
    liftGoto(LIFT_HEIGHT_MIN, false, false);

    // re-enable driver control of affected subsystems
    driver_claw = true;
    driver_chainbar = true;
    driver_lift = true;
  }
}
