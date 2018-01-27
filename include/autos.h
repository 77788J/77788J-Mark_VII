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

// skills
void autoRunSkills();

// bullet
void autoRunBullet();

// variation 1
void autoRunLeft20Cone();
void autoRunRight20Cone();

// variation 2
void autoRunCone();

// variation 3
void autoRunLeftStationary();
void autoRunRightStationary();

// variation 4
void autoRunLeftStationaryFlip();
void autoRunRightStationaryFlip();

#ifdef __cplusplus
}
#endif

#endif
