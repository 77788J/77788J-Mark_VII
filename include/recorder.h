#ifndef RECORD_H_
#define RECORD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>

// is it recording?
#define RECORDING_ENABLED false

// print data to console
void logState(unsigned char chassis_mode);

#ifdef __cplusplus
}
#endif

#endif
