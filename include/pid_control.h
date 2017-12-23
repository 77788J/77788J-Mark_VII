#ifndef PID_CONTROL_H_
#define PID_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>

void pidRunChassis();
void updateAllPids();

#ifdef __cplusplus
}
#endif

#endif
