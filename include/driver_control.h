#ifndef DRIVER_CONTROL_H_
#define DRIVER_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>

extern bool driver_chassis;
extern bool driver_lift;
extern bool driver_mogo;

// run driver control loop
void updateDriverControl();

#ifdef __cplusplus
}
#endif

#endif
