#ifndef AUTO_PICKER_H_
#define AUTO_PICKER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>

#define LEFT 0
#define RIGHT 1
#define BLUE 0
#define RED 1

extern unsigned char auto_side;
extern unsigned char auto_color;
extern unsigned char auto_variation;

// run auto picker
void autoPickerRun();

// start a loop containing the auto picker
void autoPickerStart(void * parameter);

#ifdef __cplusplus
}
#endif

#endif
