#ifndef AUTOS_H_
#define AUTOS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>


#define BULLET_DISTANCE 230


// categories
void runAutoLeftBlue(unsigned char variation);
void runAutoRightBlue(unsigned char variation);
void runAutoLeftRed(unsigned char variation);
void runAutoRightRed(unsigned char variation);

// bullet
void autoRunBullet();

// 20 zone with 2 cones
void autoRunLeft20Cone();
void autoRunRight20Cone();

// single cone
void autoRunCone();

// stationary
void autoRunStationary();

// stationary and flip mogo
void autoRunLeftStationaryFlip();
void autoRunRightStationaryFlip();

// 5 zone with 2 cones
void autoRunLeft5Cone();
void autoRunRight5Cone();

// stationary and 5 zone with cone
void autoRunLeftStationary5();
void autoRunRightStationary5();

#ifdef __cplusplus
}
#endif

#endif
