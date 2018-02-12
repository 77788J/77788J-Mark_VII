#ifndef MACROS_H_
#define MACROS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>

// macros list
#define MACRO_AUTO_STACKER 1
#define MACRO_ASSISTED_STACKER 2

// central macro functions
extern TaskHandle task_macros;
extern unsigned char current_macro;
void stopMacro();
void macrosStartListener();
void macrosUpdate();

// auto stacker
#define MAX_STACK_SIZE 10
extern unsigned int stacksize;
void autoStackerUpdate();
void autoStackerRun();

// assisted stacker
void assistedStackerUpdate();
void assistedStackerRun();

#ifdef __cplusplus
}
#endif

#endif
