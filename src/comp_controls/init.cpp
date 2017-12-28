#include "main.h"
#include "chassis.h"
#include "mogo.h"
#include "io_control.h"

void initializeIO() {
}

void initialize() {

  // init joystick
  joystick.init(1);

  // init subsystems
  chassisInit();
  mogoInit();
}
