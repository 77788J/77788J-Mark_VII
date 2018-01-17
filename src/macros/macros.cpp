#include "macros.h"
#include "io_control.h"

TaskHandle task_macros;
unsigned char current_macro = NONE;

// kills the macro task and starts a blank one
void stopMacro() {
  taskDelete(task_macros);
  current_macro = NONE;
  macrosStartListener();
}

// start background task with macro listener
void macrosStartListener() {
  task_macros = taskRunLoop(macrosUpdate, UPDATE_INTERVAL);
}

// listen for macros and run them
void macrosUpdate() {
  autoStackerUpdate();
}
