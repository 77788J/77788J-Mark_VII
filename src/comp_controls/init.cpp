#include "main.h"
#include "chassis.h"
#include "lift.h"
#include "claw.h"
#include "mogo.h"
#include "io_control.h"

void initializeIO() {
}

void initialize() {

  // init joystick
  joystick.init(1);

  // init LCD
  lcd.init(uart1);

  // init subsystems
  chassisInit();
  mogoInit();
  liftInit();
  clawInit();
}
