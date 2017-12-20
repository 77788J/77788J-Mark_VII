#ifndef MAIN_H_
#define MAIN_H_

#include <API.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <utility.h>

void autonomous();
void initializeIO();
void initialize();
void operatorControl();

#ifdef __cplusplus
}
#endif

#endif
