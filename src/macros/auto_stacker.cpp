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
    liftGoto(10.f + (2.8f * stack_size), true, false);

    // move the chainbar into stack position
    chainbarGoto(CHAINBAR_STACK, true, false);

    // lower lift slightly to make sure cone is fully nested
    liftGoto(lift_height - 1.f, true, false);

    // open claw
    clawGoto(CLAW_OPEN, true, false);

    // raise lift to clear top cone
    liftGoto(13.5f + (2.8f * stack_size), true, false);

    // extend chainbar back into grab position
    chainbarGoto(CHAINBAR_GRAB, true, false);

    // lower lift back down
    liftGoto(LIFT_HEIGHT_MIN, true, false);

    // re-enable driver control of affected subsystems
    driver_claw = true;
    driver_chainbar = true;
    driver_lift = true;
  }
}
