#ifndef MAIN_H_
#define MAIN_H_

#include <API.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <utility.h>

#define UPDATE_INTERVAL 20

// timer, always accurate to 1ms
extern int time;
void startTimer();
void timer();

// default
void autonomous();
void initializeIO();
void initialize();
void operatorControl();

#ifdef __cplusplus
}
#endif

#endif
