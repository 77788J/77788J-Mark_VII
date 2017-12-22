#ifndef DRIVER_CONTROL_H_
#define DRIVER_CONTROL_H_
#include <main.h>

extern bool driver_chassis = true;
extern bool driver_mogo = true;

// start background task
void driverControlStart();

// run driver control loop
void driverControl();

#endif
