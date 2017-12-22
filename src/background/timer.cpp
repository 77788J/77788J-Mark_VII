#include "main.h"

int time = 0;

// run a 1ms intervals
void timer() {
  time++;
}

void startTimer() {
  time = 0;
  taskRunLoop(timer, 1);
}
