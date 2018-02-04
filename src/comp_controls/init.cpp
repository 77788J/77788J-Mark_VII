#include "main.h"
#include "chassis.h"
#include "lift.h"
#include "claw.h"
#include "goliath.h"
#include "chainbar.h"
#include "mogo.h"
#include "io_control.h"
#include "auto_picker.h"

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
  chainbarInit();
  goliathInit();

  // start auto selector task
  taskCreate(autoPickerStart, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_LOWEST);
}
