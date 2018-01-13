#ifndef AUTOS_H_
#define AUTOS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>


// categories
void runAutoLeftBlue(unsigned char variation);
void runAutoRightBlue(unsigned char variation);
void runAutoLeftRed(unsigned char variation);
void runAutoRightRed(unsigned char variation);

// variation 1
void autoRunLeftRed20Cone();
void autoRunLeftBlue20Cone();

#ifdef __cplusplus
}
#endif

#endif
