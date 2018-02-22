#ifndef AUTOS_H_
#define AUTOS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>
#include <auto_picker.h>


#define BULLET_DISTANCE 230


// categories
void runAutoLeftMogo(unsigned char variation);
void runAutoRightMogo(unsigned char variation);
void runAutoLeftBullet(unsigned char variation);
void runAutoRightBullet(unsigned char variation);
void runAutoLeftStationary(unsigned char variation);
void runAutoRightStationary(unsigned char variation);

// bullets
void autoRunBullet();
void autoRunLeftBulletMogo();
void autoRunRightBulletMogo();
void autoRunLeftBulletStationary();
void autoRunRightBulletStationary();

// 20 zone with 2 cones
void autoRunLeft20ConeMogo();
void autoRunRight20ConeMogo();
void autoRunLeft20ConeStationary();
void autoRunRight20ConeStationary();

// single cone
void autoRunCone();

// landslide
void autoRunLeftLandslideMogo();
void autoRunRightLandslideMogo();
void autoRunLeftLandslideStationary();
void autoRunRightLandslideStationary();

// stationary
void autoRunStationary();

// 5 zone with 2 cones
void autoRunLeft5ConeMogo();
void autoRunRight5ConeMogo();
void autoRunLeft5ConeStationary();
void autoRunRight5ConeStationary();

// stationary and 5 zone with cone
void autoRunLeftStationary5();
void autoRunRightStationary5();

#ifdef __cplusplus
}
#endif

#endif
